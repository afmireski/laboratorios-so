# Makefile para Compilação dos Programas de FIFO

# Nomes dos executáveis
EXEC1 = envia_expressao_fifo
EXEC2 = realiza_calculo_fifo

# Arquivos fonte
SRC1 = envia_expressao_fifo.c
SRC2 = realiza_calculo_fifo.c

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99

# Regra padrão
all: $(EXEC1) $(EXEC2)

# Compilação do primeiro programa
$(EXEC1): $(SRC1)
	gcc $(CFLAGS) -o $@ $^

# Compilação do segundo programa
$(EXEC2): $(SRC2)
	gcc $(CFLAGS) -o $@ $^

# Limpeza dos arquivos compilados
clean:
	rm -f $(EXEC1) $(EXEC2)

# Execução dos programas
run: all
	./$(EXEC1) & ./$(EXEC2)

.PHONY: all clean run
