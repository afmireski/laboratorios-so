CC = clang -Wall

EX1 = process_tree

EX2 = pather_wait_child

EX3 = distributed_search

EX4 = custom_shell

PROGS=$(EX1) $(EX2) $(EX3) $(EX4)

all: $(PROGS)

$(EX1):
	$(CC) $(EX1).c -o $(EX1)

$(EX2):
	$(CC) $(EX2).c -o $(EX2)

$(EX3):
	$(CC) $(EX3).c -o $(EX3)

$(EX4):
	$(CC) $(EX4).c -o $(EX4)

clean:
	rm $(PROGS)