@echo off
REM Hybrid Inventory Manager Build Script for Windows

echo ========================================
echo Building Hybrid Inventory Manager...
echo ========================================

REM Compile C backend
echo Compiling C backend (inventory.c)...
gcc -Wall -Iinclude -c src/inventory.c -o inventory.o
if %errorlevel% neq 0 (
    echo ERROR: Failed to compile inventory.c
    exit /b 1
)

REM Compile C++ frontend
echo Compiling C++ frontend (InventoryManager.cpp)...
g++ -Wall -Iinclude -c src/InventoryManager.cpp -o InventoryManager.o
if %errorlevel% neq 0 (
    echo ERROR: Failed to compile InventoryManager.cpp
    exit /b 1
)

REM Compile main
echo Compiling main.cpp...
g++ -Wall -Iinclude -c src/main.cpp -o main.o
if %errorlevel% neq 0 (
    echo ERROR: Failed to compile main.cpp
    exit /b 1
)

REM Link all object files
echo Linking object files...
g++ inventory.o InventoryManager.o main.o -o app.exe
if %errorlevel% neq 0 (
    echo ERROR: Failed to link object files
    exit /b 1
)

echo.
echo ========================================
echo Build successful! 
echo Run 'app.exe' to start the program
echo ========================================
