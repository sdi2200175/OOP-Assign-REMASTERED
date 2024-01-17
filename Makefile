# 
# +------------------------------------+
# |	Project Makefile									 |
#	+------------------------------------+
#
#	This makefile contains the following rules:
#
#	- 
#

CC = g++

# - Compiler Options - #

CFLAGS = -Wall -Werror
LFLAGS = -lm

# - Final Executable Compilation Options - #

# Uncomment the following line if you want to
# make an executable for DEBUGGING and TESTING purposes.
CFLAGS += -g

# Uncomment the following line if you want to 
# make an executable for PRODUCTION and DISTRIBUTION purposes.
# CFLAGS += -O2

# - Executable File Options - #

EXEC_NAME = Build
EXEC_VER = 0.0.1
EXEC_FILE_EXTENSION = exe

# - File Paths - #

INCLUDE = include
SOURCE = source
BUILD_DIR = build

# - Object Files and Final Executable Name - #

OBJECTS = $(SOURCE)/main.o $(SOURCE)/interface.o $(SOURCE)/secretary.o $(SOURCE)/person.o $(SOURCE)/student.o # $(SOURCE)/professor.o
BINARY = $(BUILD_DIR)/$(EXEC_NAME)-$(EXEC_VER).$(EXEC_FILE_EXTENSION)

# - Makefile Rules - #

all: $(OBJECTS)
	@$(CC) $(LFLAGS) -I$(INCLUDE) $(OBJECTS) -o $(BINARY)
	@echo "[MAKE]:     Compilation completed Successfully. Final Executable is placed in $(BINARY)"

%.o: %.cpp
	@echo "[MAKE]:     Compiling $^..."
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $^ -o $@
	@echo "[MAKE]:     Compiled $^ successfully. Output file: $@"

run: all
	@echo "[RUN]:      Running $(BINARY)..."
	@./$(BINARY)

clean: 
	@echo "[CLEAN]:    Cleaning Residual Files..."
	@rm -f $(OBJECTS)
	@echo "[CLEAN]:    Done"

valgrind:
	@echo "[VALGRIND]: Running $(BINARY) with Valgrind Memcheck..."
	@valgrind --leak-check=full ./$(BINARY)