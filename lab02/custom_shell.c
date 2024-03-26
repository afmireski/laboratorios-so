#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h> // pid_t
#include <unistd.h> // fork, system
#include <sys/wait.h> // wait

int main(){
    

    char* exitCommand = "exit";
    int maxArgumentsCount = 10;
    
    char input[200];
    printf("------------------|SHELL|------------------\n");
    printf("Informe o comando que deseja executar. Ex: 'ls -al'\n");
    printf("'exit' para sair\n");
    printf("> ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove o caractere de nova linha

    char aux[100];
    char delimiter[2] = " ";
    strcpy(aux, input);

    // O primeiro token é o comando
    char* token = strtok(aux, delimiter); 
    if (strcmp(token, exitCommand) == 0) {
        printf("Saindo...\n");
        return 0;
    }

    char** arguments = (char**) malloc(maxArgumentsCount+1 * sizeof(char*));
    arguments[0] = token;

    int i;
    for (i = 1; token != NULL && i <= maxArgumentsCount; i++) {
        // Obtém os argumentos do comando;
        token = strtok(NULL, delimiter);
        arguments[i] = token;
        
    }
    if (arguments[maxArgumentsCount] != NULL) arguments[maxArgumentsCount] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        printf("Sou o filho chamando exec\n");
        int status = execvp(token, arguments);

        printf("Status: %d\n", status);
        if (status < 0) {
            printf("Falha ao executar comando");
            return 1;
        }
    } else {
        printf("Sou o pai\n");
        // Se é o pai talvez espere o filho
        wait(NULL);
        free(arguments);
        free(token);
    }

    printf("-------------------------------------------\n");

    exit(0);
    return 0;
}