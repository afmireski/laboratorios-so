#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define FILENAME "data.txt"

FILE *file; // Variável global para o arquivo

// Função para lidar com os sinais SIGINT e SIGTERM
void sig_handler(int signo) {
    if (signo == SIGINT || signo == SIGTERM) {
        printf("Received signal %d. Gracefully stopping...\n", signo);

        // Fechar o arquivo se estiver aberto
        if (file != NULL) {
            fclose(file);
            printf("File closed.\n");
        }

        exit(EXIT_SUCCESS);
    }
}

int main(void) {
    // Associar a função tratadora de sinais aos sinais SIGINT e SIGTERM
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("Can't catch SIGINT");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGTERM, sig_handler) == SIG_ERR) {
        perror("Can't catch SIGTERM");
        exit(EXIT_FAILURE);
    }

    // Abrir o arquivo para escrita
    file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    printf("File opened.\n");

    // Simular operações de escrita no arquivo
    fprintf(file, "Example data\n");
    printf("Data written to file.\n");

    // Mantenha o programa em execução
    while (1) {
        sleep(1);
    }

    return 0;
}
