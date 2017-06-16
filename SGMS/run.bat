@echo off
cd build
cmake .. -G "MinGW Makefiles"
make
cd ..
rd /S /Q build
md build
cd bin
pause
cls
main.exe