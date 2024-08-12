# Nome dos compiladores
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c11

# Nome dos executáveis
EXECS = exercicioA exercicioB exercicioC

# Alvos principais (executáveis)
all: $(EXECS)

exercicioA: exercicioA.o
	$(CC) $(CFLAGS) -o exercicioA exercicioA.o

exercicioB: exercicioB.o
	$(CC) $(CFLAGS) -o exercicioB exercicioB.o

exercicioC: exercicioC.o
	$(CC) $(CFLAGS) -o exercicioC exercicioC.o

# Compilação dos arquivos .o
exercicioA.o: exercicioA.c
	$(CC) $(CFLAGS) -c exercicioA.c

exercicioB.o: exercicioB.c
	$(CC) $(CFLAGS) -c exercicioB.c

exercicioC.o: exercicioC.c
	$(CC) $(CFLAGS) -c exercicioC.c

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXECS) *.o

