#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h> // pid_t
#include <unistd.h> // fork, system
#include <math.h> // pow

void create_process(int limit, int level, pid_t father);

int main(int argc, char const *argv[])
{
    if (argc > 1) {
        int n = atoi(argv[1]);
        int tree_level = 1; // O processo atual conta para a contagem
        pid_t father_pid = getpid();

        create_process(n, tree_level, father_pid);
        if (getpid() == father_pid) {
            char command[20];
            sprintf(command, "pstree %d -p -c", father_pid);

            system(command);
        }
    }

    exit(0);
    return 0;
}

void create_process(int limit, int level, pid_t father) {
    if (level >= limit) return;
    pid_t child = fork();
    if (child == 0) {
        printf("Processo %d é filho de %d\n", getpid(), father);
        create_process(limit, level+1, getpid());
        exit(0); // Encerra o filho
    } else {  // Se for o pai tenta criar um outro filho        
        create_process(limit, level, getpid());
    }
    return;
}
