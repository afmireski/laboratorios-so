/**
 * Program: geometric_mean.c
 * Descrição: usar pthreads para calcular a média geométrica de cada coluna de uma matriz MxN e devolver o resultado em um vetor de tamanho N.
 * Autor: Alexandre Tolomeotti Enokida
 * Data: 08/04/2024
 * Data de entrega: 09/04/2024
*/

#include <stdio.h>
#include <stdlib.h>    // atoi
#include <string.h>
#include <stdbool.h>   // bool
#include <pthread.h> 
#include <math.h>      // pow
#include "matriz.h"
#include <unistd.h>

#define THREAD_COUNT 1
#define IN_FILE "data_matriz_%dx%d.in"
#define OUT_FILE "media_geometrica_colunas_matriz_%dx%d.out"
#define DEBUG false

/* estrutura para passar os parâmetros para as threads */
struct data_chunk {
    int num_seq;
    int coluna_inicial, coluna_final, n_linhas;
    int **matrix;
    float *media_geometrica_colunas;
};

/**
 * Monta as chunks a serem processadas pelas threads
 * 
 * @param m: quantidade de linhas da matriz 
 * @param n: quantidade de colunas da matriz
 * @param matrix: a matrix a ser processda
 * @param media_geometrica_colunas: vetor com a média aritmética de cada linha
*/
struct data_chunk** monta_chunks(int m, int n, int **matrix, float *media_geometrica_colunas);

/**
 * Destrói os chunks criados
 * 
 * @param chunks: chunks a serem destruídos
*/
void destroi_chunks(struct data_chunk **chunks);

/**
 * Função executada pelas threads para calcular a média aritmética de cada linha
 * 
 * @param param: parâmetro passado para a thread
*/
void* calcula_media_geometrica(void *param);

/**
 * Cria as threads
 * 
 * @param threads: array que receberá as threads criadas
 * @param chunks: chunks a serem processadas
*/
void cria_threads(pthread_t *threads, struct data_chunk **chunks);

/**
 * Escreve a resposta em um arquivo
 * 
 * @param media_geometrica_colunas: o resultado a ser escrito
 * @param m: quantidade de linhas da matriz
 * @param n: quantidade de colunas da matriz
*/
bool escreve_resposta(float* media_geometrica_colunas, int m, int n);

int main(int argc, char const *argv[]) 
{
    if (argc > 2) {
        int m = atoi(argv[1]);
        int n = atoi(argv[2]);
        
        char filename[100];
        sprintf(filename, IN_FILE, m, n);

        int **matrix = read_matrix_from_file(filename, &m, &n);
        if (matrix != NULL && (m > 0 || n > 0)) {            
            float *media_geometrica_colunas = (float*) calloc(m, sizeof(int));

            struct data_chunk **chunks = monta_chunks(m, n, matrix, media_geometrica_colunas);

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

            bool success = escreve_resposta(media_geometrica_colunas, m, n);

            if (!success) {
                printf("Erro ao escrever a resposta\n");
            }

            free(media_geometrica_colunas);
            free(matrix);
            destroi_chunks(chunks);
        }
    }

    return 0;
}

struct data_chunk** monta_chunks(int m, int n, int **matrix, float *media_geometrica_colunas) {
    struct data_chunk **chunks = (struct data_chunk**) calloc(THREAD_COUNT, sizeof(struct data_chunk*));

    // Define o tamanho de cada chunk
    int chunk_size = n / THREAD_COUNT;
    int chunk_begin = 0;
    int chunk_end = chunk_size;

    // Preenche cada chunk com os dados a serem processados
    for (int i = 0; i < THREAD_COUNT; i++) {
        #if DEBUG
            printf("chunk-size %d\n", chunk_size);
            printf("chunk-begin %d\n", chunk_begin);
            printf("chunk-end %d\n", chunk_end);
        #endif
        struct data_chunk *chunk = (struct data_chunk*)malloc(sizeof(struct data_chunk));
        chunk->num_seq = i;
        chunk->matrix = matrix;
        chunk->media_geometrica_colunas = media_geometrica_colunas;
        chunk->coluna_inicial = chunk_begin;
        chunk->coluna_final = chunk_end;
        chunk->n_linhas = m;

        chunks[i] = chunk;

        chunk_begin = chunk_end;
        chunk_end += chunk_size;

        #if DEBUG
            printf("Montou chunk %d\n", i);
        #endif
    }
    // Garante que todos os elementos serão processados
    chunks[THREAD_COUNT-1]->coluna_final = n;
    return chunks;
}

void destroi_chunks(struct data_chunk **chunks) {
    for (int i = 0; i < THREAD_COUNT; i++) {
        free(chunks[i]);
    }
    free(chunks);
}

void* calcula_media_geometrica(void *param) {
    // Obtém os dados a serem processados
    struct data_chunk *chunk = (struct data_chunk*) param; // type cast

    #if DEBUG
        printf("Processando thread %d\n", chunk->num_seq);
    #endif

    for (int i = chunk->coluna_inicial; i < chunk->coluna_final; i++) {
        float produtorio_coluna = 1;
        for (int j = 0; j < chunk->n_linhas; j++) {
            produtorio_coluna *= chunk->matrix[j][i];
        }
        float media_coluna = pow(produtorio_coluna, 1.0 / chunk->n_linhas);
        #if DEBUG
            printf("Linha %d: Soma=%d, Media=%d\n", i, soma_linha, media_linha);
        #endif
        chunk->media_geometrica_colunas[i] = media_coluna;
    }

    return NULL;
}

void cria_threads(pthread_t *threads, struct data_chunk **chunks) {
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, (void*) calcula_media_geometrica, chunks[i]);
        #if DEBUG
            printf("Criou thread %d\n", i);
        #endif
    }
}

bool escreve_resposta(float *media_geometrica_colunas, int m, int n) {
    char filename[100];
    sprintf(filename, OUT_FILE, m, n);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return false;
    }

    fprintf(file, "Média geométrica das colunas\n");
    for (int i = 0; i < n; i++) {
        fprintf(file, "Coluna %d: %.4f\n", i+1, media_geometrica_colunas[i]);
    }

    fclose(file);

    return true;
}
