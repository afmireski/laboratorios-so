#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h> // pid_t
#include <unistd.h> // fork, system
#include <math.h> // pow

void create_process(int limit, int *qty, pid_t father);

int main(int argc, char const *argv[])
{
    if (argc > 1) {
        int n = atoi(argv[1]);
        int limit = (int) pow(2, n);
        int process_qty = 1; // O processo atual conta para a contagem
        pid_t father_pid = getpid();

        create_process(limit, &process_qty, father_pid);
        if (getpid() == father_pid) {
            printf("Commando");
            char command[20];
            sprintf(command, "pstree %d -c", father_pid);

            system(command);
        }
    }

    exit(0);
    return 0;
}

void create_process(int limit, int *qty, pid_t father) {
    if (*qty >= limit) return;
    pid_t child = fork();
    if (child == 0) {
        *qty += 1;
        // printf("Processo %d é filho de %d\n", getpid(), father);
        create_process(limit, qty, getpid());
    } else {  // Se for o pai tenta criar um outro filho        
        create_process(limit, qty, getpid());
    }
    return;
}
