#!/bin/bash

mkdir ./tmp_build

cp requirements.txt ./tmp_build/requirements.txt
cp clipboard.py ./tmp_build/clipboard.py

cd ./tmp_build || echo "failed to access building folder"; exit


python3 -m venv venv
source venv/bin/activate

pip install -r requirements.txt
pip install pyinstaller

pyinstaller clipboard.py