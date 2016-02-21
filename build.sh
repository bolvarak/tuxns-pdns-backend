#!/bin/bash
## Clear the output buffer
$(which clear)
## Remove any previous build files
$(which bash) ./clean.sh
## Execute cmake
$(which cmake) .
## Compile
$(which make)

