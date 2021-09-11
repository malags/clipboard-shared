#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define XSTR(x) STR(x)
#define STR(x) #x

#ifdef __HOST_URL__
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define HOST_URL TOSTRING(__HOST_URL__) "/clipboard"
#else
#error "No URL found"
#endif

// https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
struct memory {
    char *response;
    size_t size;
};

static size_t cb(void *data, size_t size, size_t nmemb, void *userp){
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL) return 0;  /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

struct memory chunk = {0};

// ---

void post(CURL* curl, char* content){
    // header
    struct curl_slist *hs=NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

    // url
    curl_easy_setopt(curl, CURLOPT_URL, HOST_URL);
    //body
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(content));
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
    curl_easy_perform(curl);
}

void get(CURL* curl){
    curl_easy_setopt(curl, CURLOPT_URL, HOST_URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_perform(curl);
}

size_t compute_size(int argc, char* argv[]){
    if(argc == 1) return 0;

    size_t tot_size = 0;

    for(int i = 1 ; i < argc; ++i){
        tot_size += strlen(argv[i]) + 1;
    }
    return tot_size;
}

char* get_args(int argc, char* argv[]){
    size_t size = compute_size(argc, argv) + 1;
    char* dest = (char*) malloc(size * sizeof(char));

    strcpy(dest, argv[1]);
    for(int i = 2 ; i < argc; ++i){
        strcat(dest, " ");
        strcat(dest, argv[i]);
    }

    return dest;
}

int main(int argc, char *argv[]){

    bool get_c = false;

    if(argc == 2 && strcmp(argv[1],"-o") == 0) get_c = true;

    CURL *curl;
    curl = curl_easy_init();

    if(curl){
        if(get_c) get(curl);
        else {
            char* clip = get_args(argc, argv);
            printf("%s\n", clip);
            printf("post");
            char* data = malloc(20+ strlen(clip));
            strcpy(data, "{\"clipboard\":\"");
            strcat(data, clip);
            strcat(data, "\"}");
            post(curl, data);
            free(clip);
        }
    }
    curl_easy_cleanup(curl);
}