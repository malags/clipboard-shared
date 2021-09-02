import React from "react"

const clipboardy = require('clipboardy');


export function Main(){
    const url = process.env.HOST_URL + '/clipboard'

    const show_message = (message) => {
        const div = document.getElementById("snackbar");

        // Add the "show" class to DIV
        div.className = "show";
        div.innerHTML = message

        // After 3 seconds, remove the show class from DIV
        setTimeout(
            function(){ div.className = div.className.replace("show", ""); },
            2000
        );
    }

    const copy = () => {
        fetch(url)
            .then(response => response.json())
            .then(data => {
                console.log(data)
                clipboardy
                    .write(data.clipboard)
                    .then(_ => show_message("Copied to clipboard"))
                    .catch(_ => alert("failed to copy"))
            })
    }

    const paste = () => {
        clipboardy
            .read()
            .then(value => {
                const options = {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({clipboard: value})
                }
                fetch(url, options).then(value1 => console.log(value1)).then(_ => show_message("Pasted to clipboard"))
            })
            .catch(reason => {
                console.log(reason)
            })
    }



    return (
        <div className="d-grid gap-2 col-6 mx-auto">
            <button type={'button'} className={'btn btn-outline-dark btn-lg btn-block'} onClick={copy}>
                Copy
            </button>
            <button type={'button'} className={'btn btn-outline-dark btn-lg btn-block'} onClick={paste}>
                Paste
            </button>
            <div id="snackbar">
                Content
            </div>
        </div>
    )
}

