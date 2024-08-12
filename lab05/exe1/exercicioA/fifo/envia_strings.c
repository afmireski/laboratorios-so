#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "/tmp/minha_fifo"

int main() {
    int fifo_fd;

    // Criando o FIFO se não existir
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Abrindo o FIFO em modo de escrita
    fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Lendo strings digitadas pelo usuário e escrevendo no FIFO
    char input[100];
    printf("Digite uma string: ");
    fgets(input, sizeof(input), stdin);
    write(fifo_fd, input, strlen(input) + 1);

    // Fechando o FIFO
    close(fifo_fd);

    return 0;
}
