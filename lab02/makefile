CC = clang -Wall

EX1 = process_tree

EX4 = custom_shell

PROGS=$(EX1) $(EX4)

all: $(PROGS)

$(EX1):
	$(CC) $(EX1).c -o $(EX1)

$(EX4):
	$(CC) $(EX4).c -o $(EX4)

clean:
	rm $(PROGS)