#!/bin/bash

cd "$(dirname "$0")"

# Создаем директорию build, если она не существует
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake ..
make

