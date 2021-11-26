#!/bin/bash
cd "$(dirname "$0")" || exit

if [ ! -d ./tmp_build ]; then
  mkdir -v ./tmp_build
fi

echo "copying files..."
cp requirements.txt ./tmp_build/requirements.txt
cp clipboard.py ./tmp_build/clipboard.py
cp .env ./tmp_build/.env

cd ./tmp_build

echo "initializing python environment..."
python3 -m venv ./venv
source ./venv/bin/activate

echo "preparing dependencies..."
pip install -r requirements.txt
pip install pyinstaller

echo "creating package..."
pyinstaller clipboard.py

echo "moving package..."
mv dist/clipboard ../dist

echo "removing build files"
cd ..
rm -rf ./tmp_build

echo "done"
echo "see dist folder"