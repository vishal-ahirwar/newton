@echo Doing Cmake Stuff
cmake -S . -B Build -G "MinGW Makefiles"
@echo Compiling...
@echo off
cd ./Build/
mingw32-make.exe
cd ../
@echo done