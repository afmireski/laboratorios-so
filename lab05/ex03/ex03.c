/**
 * Program: ex03.c
 *
 * Descrição: Implemente um programa que realize a soma de vetores utilizando processos para fazer o cálculo, mas
 * com os vetores sendo compartilhados pelos processos. Como os espaços de memória entre os processos 
 * são isolados, um mecanismo fornecido pelo SO deve ser usado. No caso, use memória compartilhada 
 * para que todos os filhos operem sobre os dados, e pipes para a realização do despacho de trabalho 
 * (intervalo de índices no vetor). O número de elementos do vetor e o número de processos filhos deve ser 
 * fornecido pelo usuário. Por exemplo, numElementos = 1000 e numProcessos = 5, cada filho processará 
 * 200 índices; para numElementos = 1000 e numProcessos = 4, cada filho processará 250 índices.
 *
 * Autor: Alexandre Tolomeotti Enokida
 * Data: 05/05/2024
 * Data de entrega: 05/05/2024
 */

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define DSHM_NAME "ex03_dshm"
#define SSHM_NAME "ex03_sshm"

#define OUTPUT_FNAME_1 "entrada_um.out"
#define OUTPUT_FNAME_2 "entrada_dois.out"
#define OUTPUT_RESULT_FNAME "resultado.out"
#define RAND_LIMIT 250
#define MAX_ELEM 10000000

#define NUM_ELEM atoi(argv[1])
#define NUM_PROC atoi(argv[2])

#define DEBUG 0

/* Lê os caracteres do pipe e armazena em um vetor */
void read_from_pipe(int file, int *output, int print)
{
	FILE *stream;
	int c;
	stream = fdopen(file, "r");
	while (fscanf(stream, "%d", &c) == 1) {
                *output = c;
                output++;

                if (print)
                        printf("%d ", c);
        }

        if (print)
                printf("\n");

	fclose(stream);
}

/* Escreve valores no pipe. */
void write_to_pipe(int file, int n1, int n2) 
{
	FILE *stream;
	stream = fdopen(file, "w");
        fprintf(stream, "%d %d\n", n1, n2);
	fclose(stream);
}

/**
 * create_rentires() - Insere valores aleatórios em um vetor bidimensional de inteiros.
 * @array: endereço do vetor.
 * @size: tamanho do vetor.
 * @fill: tamanho dos elementos do vetor.
 * @ceiling: limite máximo de valor aleatório.
 *
 */
void create_rentries(int **array, int size, int fill, int ceiling)
{
        for (int i = 0; i < size; i++) {
                for (int j = 0; j < fill; j++) {
                        array[i][j] = rand() % ceiling;
                }
        }
}

/* Armazena valores de um vetor de inteiros em um arquivo */
void writef(char *filename, int *array, int size)
{
        FILE *file;
        int i;

        file = fopen(filename, "w");
        if (file == NULL) {
                printf("Error opening file\n");
                return;
        }

        for (i = 0; i < size; i++)
                fprintf(file, "%d ", array[i]);

        fclose(file);
}

int main(int argc, char const **argv)
{
        if (argc == 3 && NUM_ELEM < MAX_ELEM) {

                /* --------------------------- SETUP ----------------------------------------- */
                int **array_list = (int**) malloc(sizeof(int *) * 2);   // vetores de entrada
                array_list[0] = (int*) malloc(sizeof(int) * NUM_ELEM);
                array_list[1] = (int*) malloc(sizeof(int) * NUM_ELEM);
                create_rentries(array_list, 2, NUM_ELEM, RAND_LIMIT);   // gera valores aleatórios nos dois vetores de entrada.
                writef(OUTPUT_FNAME_1, array_list[0], NUM_ELEM);  // escreve valores gerados do vetor um
                writef(OUTPUT_FNAME_2, array_list[1], NUM_ELEM);  // escreve valores gerados do vetor dois
                /* --------------------------- END SETUP ------------------------------------- */
                
                /* --------------------------- TEMPORARY --------------------------- */
                pid_t pid;
                int step = NUM_ELEM / NUM_PROC;
                int start = 0;
                int end = step;
                /* --------------------------- END TEMPORARY ----------------------- */

                /* ----------- IPC DECLARATIONS AND ATTRIBUTIONS ----------- */
                int pipefd[2 * NUM_PROC];               // número de canais; cada filho tem um enlace;
                int dseg_size = sizeof(int) * NUM_ELEM; // tamanho (bytes) do segmento da memória compartilhada para os dados
                int sseg_size = sizeof(int) * NUM_PROC; // tamanho (bytes) do segmento da memória compartilhada para a sinalização dos filhos
                

                void *dptr, *sptr;
                int dshm_fd, sshm_fd;
                int created_shm = 0;
                /* ----------- END IPC DECLARATIONS AND ATTRIBUTIONS ------- */


                for (int i = 0; i < NUM_PROC; i++) {
                        int pipe_step = 2 * i;

                        if (pipe(&(pipefd[pipe_step]))) {
                                fprintf(stderr, "Falha ao criar o Pipe.\n");
                                return EXIT_FAILURE;
                        }

                        pid = fork();

                        if (!pid) {
                                close(pipefd[pipe_step + 1]); // filho fecha escrita
                                int range_values[2]; // [start, end]

                                #if DEBUG
                                        printf("I'm son %d and I'll be responsible for sum of range: ", i+1);
                                #endif
                                
                                read_from_pipe(pipefd[pipe_step], range_values, DEBUG);

                                dshm_fd = shm_open(DSHM_NAME, O_RDWR, 0666);
                                if (dshm_fd == -1) {
                                        printf("Data shared memory failed for son %d\n", i+1);
                                        exit(-1);
                                }
                                if ((dptr = mmap(0, dseg_size, PROT_WRITE, MAP_SHARED, dshm_fd, 0)) == MAP_FAILED) {
                                        printf("Data mmap failed. Son %d.\n", i+1);
                                        return -1;
                                }

                                sshm_fd = shm_open(SSHM_NAME, O_RDWR, 0666);
                                if (sshm_fd == -1) {
                                        printf("Signal shared memory failed for son %d\n", i+1);
                                        exit(-1);
                                }
                                if ((sptr = mmap(0, sseg_size, PROT_WRITE, MAP_SHARED, sshm_fd, 0)) == MAP_FAILED) {
                                        printf("Signal mmap failed. Son %d.\n", i+1);
                                        return -1;
                                }

                                // filho realiza a soma dos valores dos vetores de entrada e armazena na memória compartilhada de dados
                                for (int j = range_values[0]; j < range_values[1]; j++) {
                                        ((int*) dptr)[j] = array_list[0][j] + array_list[1][j]; // typecast em dptr pois é um ponteiro void
                                }

                                ((int*) sptr)[i] = 1; // filho sinaliza na memória compartilhada de sinais que terminou
                                                      // typecast em sptr pois é um ponteiro void
                                
                                return EXIT_SUCCESS;

                        } else {
                                close(pipefd[pipe_step]); // pai fecha leitura

                                /* A condição abaixo cria o segmento, configura, e mapeia a memória compartilhada pela primeira vez. (dados e sinalização)
                                   Poderia ter feito fora do laço de repetição, porém não queria que os filhos herdassem o código de criação. */
                                if (!created_shm) {
                                        dshm_fd = shm_open(DSHM_NAME, O_CREAT | O_RDWR, 0666);
                                        ftruncate(dshm_fd, dseg_size);
                                        if ((dptr = mmap(0, dseg_size, PROT_READ, MAP_SHARED, dshm_fd, 0)) == MAP_FAILED) {
                                                printf("Data mmap failed for father proc\n");
                                                return -1;
                                        }

                                        sshm_fd = shm_open(SSHM_NAME, O_CREAT | O_RDWR, 0666);
                                        ftruncate(sshm_fd, sseg_size);
                                        if ((sptr = mmap(0, sseg_size, PROT_READ, MAP_SHARED, sshm_fd, 0)) == MAP_FAILED) {
                                                printf("Signal mmap failed for father proc\n");
                                                return -1;
                                        }

                                        created_shm = 1;
                                }

                                if (i == NUM_PROC - 1)
                                        end = NUM_ELEM;
                                
                                char tmp_start[50];
                                char tmp_end[50];
                                sprintf(tmp_start, "%d", start);
                                sprintf(tmp_end, "%d", end);

                                write_to_pipe(pipefd[pipe_step + 1], start, end);
                        }

                        start = end;
                        end += step;
                }

                int i = 0;
                while (i < NUM_PROC) {
                        if (((int*) sptr)[i] == 1) {
                                i++;
                        }
                }

                #if DEBUG
                        for (int j = 0; j < NUM_ELEM; j++) {
                                printf("%d ", ((int*) dptr)[j]);
                        }
                        printf("\n");
                #endif

                writef(OUTPUT_RESULT_FNAME, (int*) dptr, NUM_ELEM);
                if (shm_unlink(SSHM_NAME) == -1) {
                        printf("Error removing %s\n", SSHM_NAME);
                        exit(-1);
                }

                free(array_list[0]);
                free(array_list[1]);
                free(array_list);
                return 0;

        } else if (NUM_ELEM >= MAX_ELEM) {
                printf("Number of elements exceeds maximum value\n");
                return -1;

        } else {
                printf("Bad usage\nTry: ./ex03 <num_elem> <num_proc>\n");
                return -1;
        }
}