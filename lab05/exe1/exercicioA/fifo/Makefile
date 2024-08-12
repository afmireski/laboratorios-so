CC = clang -Wall

ENVIASTRING = envia_strings

RECEBEINFO = recebe_exibe_info

PROGS=$(ENVIASTRING) $(RECEBEINFO)

all: $(PROGS)

$(ENVIASTRING):
	$(CC) $(ENVIASTRING).c -o $(ENVIASTRING)

$(RECEBEINFO):
	$(CC) $(RECEBEINFO).c -o $(RECEBEINFO)

clean:
	rm $(PROGS)

enviar_string:
	./$(ENVIASTRING)

recebe_info:
	./$(RECEBEINFO)