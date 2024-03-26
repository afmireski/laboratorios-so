CC = clang -Wall

EX1 = process_tree

EX2 = custom_shell

PROGS=$(EX1) $(EX2)

all: $(PROGS)

$(EX1):
	$(CC) $(EX1).c -o $(EX1)

$(EX2):
	$(CC) $(EX2).c -o $(EX2)

clean:
	rm $(PROGS)