# Hybrid Inventory Manager Makefile for Windows
# Compiles C backend and C++ frontend

CC = gcc
CXX = g++
CFLAGS = -Wall -Iinclude
CXXFLAGS = -Wall -Iinclude
TARGET = app.exe

# Object files
OBJS = inventory.o InventoryManager.o main.o

# Default target
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)
	@echo.
	@echo Build successful! Run 'make run' to execute the program.

# Compile C source
inventory.o: src/inventory.c include/inventory.h
	$(CC) $(CFLAGS) -c src/inventory.c -o inventory.o

# Compile C++ sources
InventoryManager.o: src/InventoryManager.cpp include/inventory.h
	$(CXX) $(CXXFLAGS) -c src/InventoryManager.cpp -o InventoryManager.o

main.o: src/main.cpp include/inventory.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

# Run the program
run: $(TARGET)
	.\$(TARGET)

# Clean build artifacts
clean:
	@if exist *.o del *.o
	@if exist $(TARGET) del $(TARGET)
	@if exist inventory.dat del inventory.dat
	@echo Clean complete!

# Clean only object files (keep executable and data)
clean-obj:
	@if exist *.o del *.o
	@echo Object files cleaned!

# Help target
help:
	@echo Available targets:
	@echo   make all       - Build the project
	@echo   make run       - Build and run the program
	@echo   make clean     - Remove all build artifacts and data
	@echo   make clean-obj - Remove only object files
	@echo   make help      - Show this help message

.PHONY: all run clean clean-obj help
