# Nome do compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -std=c11

# Nomes dos programas
TARGETS = lerstringpipe exibe_info

all: $(TARGETS)

# Regras para compilar lerstringpipe
lerstringpipe: lerstringpipe.c
	$(CC) $(CFLAGS) -o lerstringpipe lerstringpipe.c

# Regras para compilar exibe_info
exibe_info: exibe_info.c
	$(CC) $(CFLAGS) -o exibe_info exibe_info.c

# Limpeza dos arquivos compilados
clean:
	rm -f $(TARGETS)

# Regra para executar o programa principal
run: $(TARGETS)
	./lerstringpipe

.PHONY: all clean run
