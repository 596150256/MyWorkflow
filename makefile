CC = g++

CFLAGS = -c -Wall

LDFLAGS = 

EXECUTABLE = test

all: $(EXECUTABLE)

$(EXECUTABLE): SubTask.o test.o
	$(CC) $(LDFLAGS) SubTask.o test.o -o $@

SubTask.o: SubTask.cpp SubTask.h
	$(CC) $(CFLAGS) SubTask.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

clean:
	del /Q /F *.o $(EXECUTABLE)