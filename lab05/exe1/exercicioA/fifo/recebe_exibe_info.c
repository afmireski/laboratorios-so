#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "/tmp/minha_fifo"

int main() {
    int fifo_fd;
    char input[100];

    // Abrindo o FIFO em modo de leitura
    fifo_fd = open(FIFO_NAME, O_RDONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Lendo a string do FIFO
    read(fifo_fd, input, sizeof(input));

    // Calculando informações sobre a string
    int length = strlen(input) - 1; // Desconsiderando o caractere de nova linha
    int vowels = 0, consonants = 0, spaces = 0;

    for (int i = 0; i < length; i++) {
        char ch = input[i];

        if (ch == ' ') {
            spaces++;
        } else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
                ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
                vowels++;
            } else {
                consonants++;
            }
        }
    }

    // Exibindo informações sobre a string
    printf("String: %s", input);
    printf("Tamanho: %d\n", length);
    printf("Número de consoantes: %d\n", consonants);
    printf("Número de vogais: %d\n", vowels);
    printf("Número de espaços: %d\n", spaces);

    // Fechando o FIFO
    close(fifo_fd);

    return 0;
}
