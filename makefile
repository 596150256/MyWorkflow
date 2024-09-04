CC = gcc

CFLAGS = -c -Wall

LDFLAGS = 

EXECUTABLE = test

all: $(EXECUTABLE)

$(EXECUTABLE): SubTask.o test.o
	$(CC) $(LDFLAGS) SubTask.o test.o -o $@

SubTask.o: SubTask.cc SubTask.h
	$(CC) $(CFLAGS) SubTask.cc

test.o: test.cc
	$(CC) $(CFLAGS) test.cc

clean:
	del /Q /F *.o $(EXECUTABLE)