@echo off
REM Clean build artifacts

echo Cleaning build artifacts...

if exist *.o del *.o
if exist app.exe del app.exe
if exist inventory.dat del inventory.dat

echo Clean complete!
