# clipboard-shared

Small web application that hosts a shared clipboard.

## Usage

### 
Change the `HOST_URL` inside the `.env` file to the IP of the host machine.

Run `docker-compose up` from this folder.

Go to `HOST_URL`

## CLI
The CLI of the application is currently in python, to use it run

`clipboard.py <SOME_DATA>` to save to shared clipboard

`clipboard.py` to output the shared clipboard to terminal
