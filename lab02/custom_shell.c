#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcpy, strlen, strcmp, strtok
#include <stdbool.h> // Suporte a true e false
#include <sys/types.h> // pid_t
#include <unistd.h> // fork, system
#include <sys/wait.h> // wait

int main(){
    char* exitCommand = "exit";
    int maxArgumentsCount = 10;
    
    while (1) {
        char input[200];
        printf("\n------------------|SHELL|------------------\n");
        printf("Informe o comando que deseja executar. Ex: 'ls -al'\n");
        printf("*'exit' para sair\n");
        printf("*Máximo de %d argumentos por comando\n", maxArgumentsCount);
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove o caractere de nova linha

        char aux[200];
        char delimiter[2] = " ";
        strcpy(aux, input);

        // O primeiro token é o comando
        char* token = strtok(aux, delimiter);
        
        // Verifica se o token é 'exit', ou, caso comando único, se ele é 'exit'.
        if (strlen(token) == 0) {
            if (strcmp(aux, exitCommand) == 0) {
                printf("Saindo...\n");
                break;
            }
            strcpy(token, aux);
        } else if (strcmp(token, exitCommand) == 0) {
            printf("Saindo...\n");
            break;
        }        
       
        char** arguments = (char**) calloc(maxArgumentsCount+1, sizeof(char*));
        arguments[0] = token;
        bool isBackground = false;

        int i;
        for (i = 1; token != NULL && i < maxArgumentsCount; i++) {
            // Obtém os argumentos do comando;
            token = strtok(NULL, delimiter);
            if (token != NULL) {
                if (strcmp(token, "&") == 0) isBackground = true;
            }
            arguments[i] = token;
            
        }
        if (arguments[maxArgumentsCount] != NULL) arguments[maxArgumentsCount] = NULL;
        pid_t pid = fork();
        if (pid == 0) {
            int status = execvp(arguments[0], arguments);

            printf("Status: %d\n", status);
            if (status < 0) {
                printf("Falha ao executar comando");
                return 1;
            }
        } else {
            // É o pai
            // Verifica se o comando do exec executará em segundo plano
            if (!isBackground) {
                // Se não, espera terminar
                wait(NULL);
                // Limpar a memória alocada manualmente
                free(arguments);
                free(token);
            }
        }
        printf("\n-------------------------------------------\n");
    }

    exit(0);
    return 0;
}