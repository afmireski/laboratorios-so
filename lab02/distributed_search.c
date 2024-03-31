/**
 * Autor: Alexandre Tolomeotti Enokida.
 * Data: 29/03/2024.
 * Última atualização: 30/04/2024.
*/

#include <stdio.h>        // printf()
#include <stdlib.h>       // exit()
#include <unistd.h>       // fork()
#include <stdlib.h>       // rand()
#include <sys/types.h>    // pid_t
#include <sys/wait.h>     // wait() 
#include "distributed_search.h"

int find(int *array, int size, int value, int *index) 
{
        for(int i = 0; i < size; i++) {
                if(array[i] == value) {
                        *index = i;
                        return 1;
                }
        }

        *index = -1;
        return 0;
}

pid_t distributed_search(int *ar, int size, int childs, int value) 
{
        int i, status, index;
        pid_t pid;

        int step = size / childs; // definição do tamanho do "subvetor" de cada processo filho.
        int start = 0;
        int end = step;

        for(i = 0; i < childs; i++) {
                pid = fork();
                
                if(pid == 0) {
                        if(i == childs - 1) // último filho sempre recebe o restante do vetor.
                                end = size;

                        if(find(ar + start, end - start, value, &index)) {
                                index = i * step + (index); // calcula o índice real do valor no vetor.
                                printf("Valor %d encontrado no índice %d\n", value, index);
                                exit(0);
                        }
                        exit(1);
                }

                // a atribuição e incremento de start e end é feita fora do if porque senão o start do pai sempre será 0.
                start = end; // atualiza o início do vetor para o próximo filho.
                end += step; // atualiza o final do vetor para o próximo filho.
        }

        for(i = 0; i < childs; i++) {
                pid = wait(&status);
                if (!status) // status só sera 0 se o valor for encontrado.
                        return pid; // se encontrou, retorna o Process ID.
        }

        return -1;
}

int main(int argc, char const **argv)
{
        if (argc == 5) { // bin; array size; number of children; value to search; max value in array;
                int *array = (int *) malloc(atoi(argv[1]) * sizeof(int));

                for(int i = 0; i < atoi(argv[1]); i++) { // inserindo no array valores aleatórios de 0 à max value.
                        array[i] = rand() % atoi(argv[4]);
                        printf("%d\n", array[i]);
                }

                // EXIBE SOMENTE O PRIMEIRO PROCESSO QUE ENCONTRAR O VALOR.
                pid_t pid = distributed_search(array, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
                
                if (pid == -1)
                        printf("Valor não encontrado\n");
                else
                        printf("Valor encontrado pelo processo %d\n", pid);
                

        }
        
        return 0;
        
}