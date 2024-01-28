# 
# +-------------------------------------+
# |			Project Makefile			|
# +-------------------------------------+
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

EXEC_NAME = UniManagement
EXEC_VER = 1.0
EXEC_FILE_EXTENSION = exe

# - File Paths - #

INCLUDE = inc
SOURCE = src
BUILD_DIR = .

# - Object Files and Final Executable Name - #

OBJECTS = $(SOURCE)/main.o $(SOURCE)/interface/interface.o $(SOURCE)/interface/student.o $(SOURCE)/interface/professor.o $(SOURCE)/interface/course.o $(SOURCE)/secretary/secretary.o $(SOURCE)/secretary/person.o $(SOURCE)/secretary/course.o
BINARY = $(BUILD_DIR)/$(EXEC_NAME)-$(EXEC_VER).$(EXEC_FILE_EXTENSION)

# - Makefile Rules - #

all: $(OBJECTS)
	@$(CC) $(LFLAGS) -I$(INCLUDE) $(OBJECTS) -o $(BINARY)
	@echo "[MAKE]:     Compilation completed Successfully. Final Executable is placed in $(BINARY)"
	@echo "[CLEAN]:    Cleaning Residual Files..."
	@rm -f $(OBJECTS)
	@echo "[CLEAN]:    Done"

%.o: %.cpp
	@echo "[MAKE]:     Compiling $^..."
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $^ -o $@

run: all
	@echo "[RUN]:      Running $(BINARY)..."
	@echo ""
	@./$(BINARY)

clean: 
	@echo "[CLEAN]:    Cleaning Residual Files..."
	@rm -f $(OBJECTS) $(BINARY)
	@echo "[CLEAN]:    Done"

valgrind: all
	@echo "[VALGRIND]: Running $(BINARY) with Valgrind Memcheck..."
	@valgrind --leak-check=full ./$(BINARY)