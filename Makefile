CC = gcc
CFLAGS = -Wall -O3 -g
TARGET = nonogram
OBJ = board.o solve.o set.o
RM = rm -rf

all: $(TARGET)

$(TARGET): $(OBJ) nonogram.o
	$(CC) -o $@ $^ $(CFLAGS)

nonogram.o: nonogram.c board.h solve.h
	$(CC) -c nonogram.c $(CFLAGS)

board.o: board.c
	$(CC) -c $^ $(CFLAGS)

solve.o: solve.c
	$(CC) -c $^ $(CFLAGS)

set.o: set.c
	$(CC) -c $^ $(CFLAGS)

run: $(TARGET)
	./$(TARGET) input_data

test: test.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) && ./test

test.o: test.c
	$(CC) -c $^ $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJ) test test.o nonogram.o

