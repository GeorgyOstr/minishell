#!/bin/bash

echo "[1] normal env"
./minishell
echo "status=$?"

echo "[2] empty env"
env -i ./minishell
echo "status=$?"

echo "[3] bash empty env reference"
env -i bash -c 'exit 0'
echo "bash status=$?"
