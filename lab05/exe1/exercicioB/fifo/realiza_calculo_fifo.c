#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "/tmp/calculadora_fifo1"

int main() {
    int fifo_fd;
    char expression[100];

    // Abrindo o FIFO em modo de leitura
    fifo_fd = open(FIFO_NAME, O_RDONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Lendo a expressão matemática do FIFO
    read(fifo_fd, expression, sizeof(expression));

    // Realizando o cálculo da expressão
    int num1, num2;
    char operator;
    sscanf(expression, "%d %c %d", &num1, &operator, &num2);

    int result;
    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printf("Erro: Divisão por zero.\n");
                return EXIT_FAILURE;
            }
            result = num1 / num2;
            break;
        default:
            printf("Operador inválido.\n");
            return EXIT_FAILURE;
    }

    // Exibindo o resultado
    printf("Resultado: %d\n", result);

    // Fechando o FIFO
    close(fifo_fd);

    return 0;
}
