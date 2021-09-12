# clipboard-shared

Small web application that hosts a shared clipboard.

GUI with two buttons:
- Copy: shared clipboard -> clipboard
- Paste: clipboard -> shared clipboard

## Usage
Change the `HOST_URL` inside the `.env` file to the IP of the host machine.

Run `docker-compose up` from this folder.

Go to `HOST_URL`

## CLI

There are two CLI versions available, both have the same interface

### Python version
Run with

`./clipboard.py <SOME_DATA>` to save to shared clipboard

`./clipboard.py -o` to output the shared clipboard to terminal

### C version
Compile with `make` then run with

`./clipboard <SOME_DATA>` to save to shared clipboard

`./clipboard -o` to output the shared clipboard to terminal