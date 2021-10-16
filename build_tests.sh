#!/usr/bin/env bash
set -e

THIRD_PARTY="third_party.txt"
SRC="test"

# Set environment variables in third_party.txt
export $(grep -v '^#' ${THIRD_PARTY} | xargs)

g++ -std=c++17 \
    -Iinclude \
    -I"${GTEST_PATH}/include" \
    -L"${GTEST_PATH}/lib" \
    -lgtest \
    -o "${SRC}/test.app" "${SRC}/main.cpp"

# Unset all environment variables previously set by third_party.txt
unset $(grep -v '^#' ${THIRD_PARTY} | sed -E 's/(.*)=.*/\1/' | xargs)
