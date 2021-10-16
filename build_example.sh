#!/usr/bin/env bash
set -e

SRC="example"

g++ -std=c++17 \
    -Iinclude \
    -o "${SRC}/example.app" "${SRC}/example.cpp"
