CC = gcc

EX1 = process_tree

EX3 = distributed_search

EX4 = custom_shell

PROGS=$(EX1) $(EX3) $(EX4)

all: $(PROGS)

$(EX1):
	$(CC) $(EX1).c -o $(EX1)

$(EX3):
	$(CC) $(EX3).c -o $(EX3)

$(EX4):
	$(CC) $(EX4).c -o $(EX4)

clean:
	rm $(PROGS)