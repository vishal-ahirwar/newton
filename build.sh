#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Generate build files
echo -e "${GREEN}[ccli]: Generating build files...${NC}"
cmake -S . -B build
echo ""

# Build the project 
echo -e "${GREEN}[ccli]: Building the project...${NC}"
cmake --build build
echo ""

# # Install
# echo -e "${GREEN}[ccli]: Installing ccli...${NC}"
# sudo cmake --build build --target install
# echo ""
