#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int main() {
    // Criando o pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Criando o processo filho
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Processo pai
        // Fechando o lado de leitura do pipe
        close(pipe_fd[READ_END]);

        // Lendo strings digitadas pelo usuário
        char input[100];
        printf("Digite uma string: ");
        fgets(input, sizeof(input), stdin);

        // Escrevendo a string no pipe
        write(pipe_fd[WRITE_END], input, strlen(input) + 1);

        // Fechando o lado de escrita do pipe
        close(pipe_fd[WRITE_END]);
    } else { // Processo filho
        // Fechando o lado de escrita do pipe
        close(pipe_fd[WRITE_END]);

        // Redirecionando a entrada padrão para o pipe
        dup2(pipe_fd[READ_END], STDIN_FILENO);

        // Executando o outro programa
        execl("./exibe_info", "exibe_info", NULL);

        // Se o execl falhar
        perror("execl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
