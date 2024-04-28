CC = clang -Wall

CLIENT = ex04_client

SERVER = ex04_server

PROGS=$(CLIENT) $(SERVER)

all: $(PROGS)

$(CLIENT):
	$(CC) $(CLIENT).c -o $(CLIENT)

$(SERVER):
	$(CC) $(SERVER).c -o $(SERVER)

clean:
	rm $(PROGS)

server: 
	./$(SERVER)

client: 
	./$(CLIENT)
