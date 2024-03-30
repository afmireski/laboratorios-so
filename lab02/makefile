CC = gcc

EX1 = process_tree

EX2 = distributed_search

EX4 = custom_shell

PROGS=$(EX1) $(EX2) $(EX4)

all: $(PROGS)

$(EX1):
	$(CC) $(EX1).c -o $(EX1)

$(EX2):
	$(CC) $(EX2).c -o $(EX2)

$(EX4):
	$(CC) $(EX4).c -o $(EX4)

clean:
	rm $(PROGS)