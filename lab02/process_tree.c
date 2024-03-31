/**
 * Autor: André Felipe Mireski
 * Data de entrega: 30/03/2024
 * Última atualização: 30/04/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Suporte a true e false
#include <sys/types.h> // pid_t
#include <unistd.h> // fork, system
#include <sys/wait.h> // wait

void create_process(int limit, int level);

int main(int argc, char const *argv[])
{
    if (argc > 1) {
        int n = atoi(argv[1]);
        int tree_level = 1; // O processo atual conta para a contagem
        pid_t father_pid = getpid();

        create_process(n, tree_level);

        if (getpid() == father_pid) {
            char command[20];
            sprintf(command, "pstree %d -p", father_pid);
            system(command);
        } else {
            getchar();
        }
        exit(0);
    }
    return 0;
}

void create_process(int limit, int level) {
    if (level >= limit) {
        return;
    };
    pid_t left_child_pid = fork();
    if (left_child_pid == 0) {
        create_process(limit, level+1); // Filho pode tentar ser pai
    } else {  // Se for o pai tenta criar um outro filho        
        pid_t right_child_pid = fork();
        if (right_child_pid == 0) {
            create_process(limit, level+1); // Filho pode tentar ser pai
        }
    }
    return;
}
