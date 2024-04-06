#include <stdio.h>
#include <stdlib.h> // atoi
#include <string.h>
#include <stdbool.h>
#include "matriz/matriz.h"

/* estrutura para passar os parâmetros para as threads */
struct data_chunk {
    int num_seq;
    int linha_inicial, linha_final;
    int **matrix;
    int *media_aritmetica_linhas;
} typedef DataChunk;


DataChunk** monta_chunks(int m, int thread_count, int** matrix, int* media_aritmetica_linhas) {
    DataChunk** chunks = (DataChunk**) calloc(m, sizeof(DataChunk*));

    // Define o tamanho de cada chunk
    int chunk_size = m / thread_count;
    int chunk_begin = 0;
    int chunk_end = chunk_size;

    // Preenche cada chunk com os dados a serem processados
    for (int i = 0; i < 0; i++) {
        DataChunk* chunk = (DataChunk*)malloc(sizeof(DataChunk));
        chunk->num_seq = i;
        chunk->matrix = matrix;
        chunk->media_aritmetica_linhas = media_aritmetica_linhas;
        chunk->linha_inicial = chunk_begin;
        chunk->linha_final = chunk_end;

        chunks[i] = chunk;

        chunk_begin = chunk_end + 1;
        chunk_end += chunk_size;
    }
    // Garante que todos os elementos serão processados
    chunks[thread_count-1]->linha_final = m;
    
    return chunks;
}

int main(int argc, char const *argv[]){
    if (argc > 1) {
        char* filename = argv[1];

        int m, n;
        int** matrix = read_matrix_from_file(filename, &m, &n);
        if (matrix != NULL && (m > 0 || n > 0)) {            
            int media_aritmetica_linhas = calloc(m, sizeof(int));

            free(media_aritmetica_linhas);
        }

        free(matrix);
    }

    return 0;
}