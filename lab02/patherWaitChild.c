#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <comando>\n", argv[0]);
        return 1;
    }
    
    // Cria um processo filho
    pid_t pid = fork();

    if (pid < 0) {
        // Erro ao criar o processo filho
        perror("Erro ao criar processo filho");
        return 1;
    } else if (pid == 0) {
        // Este é o processo filho
        // Executa o comando passado como argumento
        if (execvp(argv[1], &argv[1]) == -1) {
            perror("Erro ao executar comando");
            return 1;
        }
    } else {
        // Este é o processo pai
        // Aguarda o término da execução do processo filho
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("O processo filho terminou com código de saída %d\n", WEXITSTATUS(status));
        } else {
            printf("O processo filho terminou de forma anormal\n");
        }
    }

    return 0;
}
