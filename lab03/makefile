CC = clang -Wall

FLAGS = -lpthread.

LIBS = matriz.o

EX1 = x

EX2a = arithmetic_average

EX2b = y

PROGS=$(EX2a)

all: $(PROGS)

$(EX1):
	$(CC) $(EX1).c $(LIBS) -o $(EX1)

$(EX2a):
	$(CC) $(EX2a).c $(LIBS) -o $(EX2a)

$(EX2b):
	$(CC) $(EX2b).c $(LIBS) -o $(EX2b)

CFLAGS=-I.
DEPS = matriz.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

matriz: matriz.o test_matriz.o 
	$(CC) -o test_matriz matriz.o test_matriz.o

clean: 
	rm *.o test_matriz $(PROGS)