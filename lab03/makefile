CC = Clang -Wall

FLAGS = -lpthread.

LIBS = matriz.o

EX1 = x

EX2a = arithmetic_average

EX2b = geometric_mean

PROGS=$(EX2a) $(EX2b)

all: $(PROGS)

$(EX1):
	$(CC) $(EX1).c $(LIBS) -o $(EX1)

$(EX2a):
	$(CC) $(EX2a).c $(LIBS) -o $(EX2a)

$(EX2b):
	$(CC) $(EX2b).c $(LIBS) -o $(EX2b) -lm

CFLAGS=-I.
DEPS = matriz.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

matriz: matriz.o test_matriz.o 
	$(CC) -o test_matriz matriz.o test_matriz.o

clean: 
	rm *.o test_matriz $(PROGS)