# Nome dos compiladores e flags
CC = gcc
CFLAGS = -Wall -g

# Nomes dos executáveis
TARGETS = envia_expressao realiza_calculo

# Regras principais
all: $(TARGETS)

envia_expressao: envia_expressao.o
	$(CC) $(CFLAGS) -o envia_expressao envia_expressao.o

realiza_calculo: realiza_calculo.o
	$(CC) $(CFLAGS) -o realiza_calculo realiza_calculo.o

# Regras de compilação
envia_expressao.o: envia_expressao.c
	$(CC) $(CFLAGS) -c envia_expressao.c

realiza_calculo.o: realiza_calculo.c
	$(CC) $(CFLAGS) -c realiza_calculo.c

# Regra de limpeza
clean:
	rm -f *.o $(TARGETS)
