/**
 * Program: arithmetic_average.c
 * Descrição: usar pthreads para calcular a média aritmética de cada linha de uma matriz MxN e devolver o resultado em um vetor de tamanho M.
 * Autor: André Felipe Mireski
 * Data: 05/04/2024
 * Data de entrega: 09/04/2024
*/

#include <stdio.h>
#include <stdlib.h> // atoi
#include <string.h>
#include <stdbool.h> // bool
#include<pthread.h> 
#include "matriz.h"

#define THREAD_COUNT 1
#define IN_FILE "data_matriz_%dx%d.in"
#define OUT_FILE "media_aritmetica_linhas_matriz_%dx%d.out"
#define DEBUG false

/* estrutura para passar os parâmetros para as threads */
struct data_chunk {
    int num_seq;
    int linha_inicial, linha_final, n_colunas;
    int **matrix;
    int *media_aritmetica_linhas;
} typedef DataChunk;

/**
 * Monta as chunks a serem processadas pelas threads
 * 
 * @param m: quantidade de linhas da matriz 
 * @param n: quantidade de colunas da matriz
 * @param matrix: a matrix a ser processda
 * @param media_aritmetica_linhas: vetor com a média aritmética de cada linha
*/
DataChunk** monta_chunks(int m, int n, int** matrix, int* media_aritmetica_linhas);

/**
 * Destrói os chunks criados
 * 
 * @param chunks: chunks a serem destruídos
*/
void destroi_chunks(DataChunk** chunks);

/**
 * Função executada pelas threads para calcular a média aritmética de cada linha
 * 
 * @param param: parâmetro passado para a thread
*/
void* calcula_media_aritmetica(void *param);

/**
 * Cria as threads
 * 
 * @param threads: array que receberá as threads criadas
 * @param chunks: chunks a serem processadas
*/
void cria_threads(pthread_t *threads, DataChunk** chunks);

/**
 * Escreve a resposta em um arquivo
 * 
 * @param media_aritmetica_linhas: o resultado a ser escrito
 * @param m: quantidade de linhas da matriz
 * @param n: quantidade de colunas da matriz
*/
bool escreve_resposta(int* media_aritmetica_linhas, int m, int n);

int main(int argc, char const *argv[]){
    if (argc > 2) {
        int m = atoi(argv[1]);
        int n = atoi(argv[2]);
        
        char filename[100];
        sprintf(filename, IN_FILE, m, n);

        int** matrix = read_matrix_from_file(filename, &m, &n);
        if (matrix != NULL && (m > 0 || n > 0)) {            
            int* media_aritmetica_linhas = (int*) calloc(m, sizeof(int));

            DataChunk** chunks = monta_chunks(m, n, matrix, media_aritmetica_linhas);

            /* Declara as threads */
            pthread_t threads[THREAD_COUNT];
            cria_threads(threads, chunks);

            /* Aguarda as threads terminarem */
            for (int i = 0; i < THREAD_COUNT; i++) {
                pthread_join(threads[i], NULL);
                #if DEBUG
                    printf("Thread %d terminou\n", i);
                #endif
            }

            bool success = escreve_resposta(media_aritmetica_linhas, m, n);

            if (!success) {
                printf("Erro ao escrever a resposta\n");
            }

            free(media_aritmetica_linhas);
            free(matrix);
            destroi_chunks(chunks);
        }
    }

    return 0;
}

DataChunk** monta_chunks(int m, int n, int** matrix, int* media_aritmetica_linhas) {
    DataChunk** chunks = (DataChunk**) calloc(THREAD_COUNT, sizeof(DataChunk*));

    // Define o tamanho de cada chunk
    int chunk_size = m / THREAD_COUNT;
    int chunk_begin = 0;
    int chunk_end = chunk_size;

    // Preenche cada chunk com os dados a serem processados
    for (int i = 0; i < THREAD_COUNT; i++) {
        #if DEBUG
            printf("chunk-size %d\n", chunk_size);
            printf("chunk-begin %d\n", chunk_begin);
            printf("chunk-end %d\n", chunk_end);
        #endif
        DataChunk* chunk = (DataChunk*)malloc(sizeof(DataChunk));
        chunk->num_seq = i;
        chunk->matrix = matrix;
        chunk->media_aritmetica_linhas = media_aritmetica_linhas;
        chunk->linha_inicial = chunk_begin;
        chunk->linha_final = chunk_end;
        chunk->n_colunas = n;

        chunks[i] = chunk;

        chunk_begin = chunk_end;
        chunk_end += chunk_size;

        #if DEBUG
            printf("Montou chunk %d\n", i);
        #endif
    }
    // Garante que todos os elementos serão processados
    chunks[THREAD_COUNT-1]->linha_final = m;  
    return chunks;
}

void destroi_chunks(DataChunk** chunks) {
    for (int i = 0; i < THREAD_COUNT; i++) {
        free(chunks[i]);
    }
    free(chunks);
}

void* calcula_media_aritmetica(void *param) {
    // Obtém os dados a serem processados
    DataChunk* chunk = (DataChunk*) param;

    #if DEBUG
        printf("Processando thread %d\n", chunk->num_seq);
    #endif

    for (int i = chunk->linha_inicial; i < chunk->linha_final; i++) {
        int soma_linha = 0;
        for (int j = 0; j < chunk->n_colunas; j++) {
            soma_linha += chunk->matrix[i][j];
        }
        int media_linha = soma_linha / chunk->n_colunas;
        #if DEBUG
            printf("Linha %d: Soma=%d, Media=%d\n", i, soma_linha, media_linha);
        #endif
        chunk->media_aritmetica_linhas[i] = media_linha;
    }

    return NULL;
}

void cria_threads(pthread_t *threads, DataChunk** chunks) {
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, (void*) calcula_media_aritmetica, chunks[i]);
        #if DEBUG
            printf("Criou thread %d\n", i);
        #endif
    }
}

bool escreve_resposta(int* media_aritmetica_linhas, int m, int n) {
    char filename[100];
    sprintf(filename, OUT_FILE, m, n);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return false;
    }

    fprintf(file, "Média Aritméticas das Linhas\n");
    for (int i = 0; i < m; i++) {
        fprintf(file, "Linha %d: %d\n", i, media_aritmetica_linhas[i]);
    }

    fclose(file);

    return true;
}
