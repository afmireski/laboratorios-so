#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Lendo a expressão matemática do pipe
    char expression[100];
    fgets(expression, sizeof(expression), stdin);

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

    return 0;
}
