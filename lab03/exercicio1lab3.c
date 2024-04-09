/**
 * Program: exercicio1lab3.c
 * Descrição: usa N threads que localiza um valor em um vetor de inteiros. O espaço de busca no
vetor deve ser distribuído para as N threads.
 * Autor: Victor Angelo Souza Santos
 * Data: 09/04/2024
 * Data de entrega: 09/04/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 200

// Estrutura para armazenar dados passados para cada thread
typedef struct {
    int **matrix;       // Matriz de inteiros
    int rows;           // Número de linhas na matriz
    int cols;           // Número de colunas na matriz
    int value;          // Valor a ser buscado
    int thread_id;      // ID da thread
    int *result;        // Resultado da busca
} ThreadData;

// Função executada por cada thread para buscar o valor na matriz
void *search(void *arg) {
    // Converte o argumento para o tipo ThreadData
    ThreadData *data = (ThreadData *)arg;

    // Calcula o intervalo de linhas a serem buscadas por esta thread
    int start_row = (data->rows / MAX_THREADS) * data->thread_id;
    int end_row = (data->thread_id == MAX_THREADS - 1) ? data->rows : (data->rows / MAX_THREADS) * (data->thread_id + 1);

    // Itera sobre as linhas atribuídas a esta thread
    for (int i = start_row; i < end_row; i++) {
        // Itera sobre as colunas da matriz
        for (int j = 0; j < data->cols; j++) {
            // Se o valor na posição atual da matriz for igual ao valor buscado
            if (data->matrix[i][j] == data->value) {
                // Calcula o índice correspondente na matriz e atualiza o resultado
                *(data->result) = i * data->cols + j;
                // Encerra a execução da thread
                pthread_exit(NULL);
            }
        }
    }

    // Encerra a execução da thread se o valor não for encontrado
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Verifica se o número correto de argumentos foi passado
    if (argc != 3) {
        printf("Usage: %s <input_file> <value_to_search>\n", argv[0]);
        return 1;
    }

    // Obtém o nome do arquivo de entrada e o valor a ser buscado dos argumentos da linha de comando
    char *filename = argv[1];
    int value = atoi(argv[2]);

    // Abre o arquivo de entrada para leitura
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    // Lê o número de linhas e colunas da matriz do arquivo
    int rows, cols;
    fscanf(file, "%dx%d", &rows, &cols);

    // Aloca memória para armazenar a matriz
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        // Lê os valores da matriz do arquivo
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    // Fecha o arquivo após a leitura ter sido concluída
    fclose(file);

    // Declara variáveis para as threads, dados da thread e o resultado da busca
    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];
    int result = -1;

    // Inicializa e cria as threads
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_data[i].matrix = matrix;
        thread_data[i].rows = rows;
        thread_data[i].cols = cols;
        thread_data[i].value = value;
        thread_data[i].thread_id = i;
        thread_data[i].result = &result;
        pthread_create(&threads[i], NULL, search, (void *)&thread_data[i]);
    }

    // Aguarda que todas as threads terminem a execução
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprime o resultado da busca
    if (result != -1) {
        printf("Value found at index: %d\n", result);
    } else {
        printf("Value not found.\n");
    }

    // Libera a memória alocada para a matriz
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
