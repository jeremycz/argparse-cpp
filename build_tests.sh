#!/usr/bin/env bash
cd test

GTEST_PATH="/opt/homebrew/Cellar/googletest/1.11.0"

g++ -std=c++17 \
    -I../include \
    -I"$GTEST_PATH/include" \
    -L"$GTEST_PATH/lib" \
    -lgtest \
    -o test.app main.cpp
