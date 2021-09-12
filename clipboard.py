#!/usr/bin/env python3

import os
from read_env import read_env
import argparse
import requests

parser = argparse.ArgumentParser()

parser.add_argument("-o", "--output", help="Get shared value", action="store_true", required=False)

args = parser.parse_known_args()

read_env()

if argparse.Namespace(output=True) in args:
    response = requests.get(url=os.environ['HOST_URL'] + '/clipboard').json()
    print(response['clipboard'], end="")
else:
    input_data = " ".join(args[1])
    requests.post(url=os.environ['HOST_URL'] + '/clipboard', json={'clipboard': input_data})

