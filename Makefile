CC = g++

LFLAGS = -lm
CFLAGS = -g -Wall -Werror

INCLUDE = -I./include
OBJECTS = source/main.o source/Course.o source/Members/Person.o source/Members/Student.o source/Members/Professor.o

EXECUTABLE = build/build.out

all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	rm -f $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

run: all
	./$(EXECUTABLE)