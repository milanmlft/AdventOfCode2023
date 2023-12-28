#!/bin/bash

set -e

NEW_DIR="day${1}"

mkdir -p "${NEW_DIR}/source"
touch ${NEW_DIR}/source/main.cpp

mkdir -p "${NEW_DIR}/data"

cp day2/CMakeLists.txt ${NEW_DIR}/
cp day2/source/CMakeLists.txt ${NEW_DIR}/source/
