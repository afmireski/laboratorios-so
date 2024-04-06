/**
 * Program: test_matriz.c
 * Descrição: testar as funções da biblioteca matriz.h
 * 
 * Autor: Rodrigo Campiolo
 * Data: 04/09/2019
 */

#include <stdio.h> 
#include <stdlib.h>     //atoi(), srand()
#include <time.h>       //time() 
#include <stdbool.h>    // bool
#include "matriz.h"

#define M 100
#define N 200
#define DEBUG false

void test_passed(bool condition, char *success_message, char *failure_message);

 /********** main - fluxo principal **********/
int main(int argc, char *argv[]) 
{ 
   int r = M, c = N, i, j, count; 
    
   /* processa as dimensões da matriz se informadas por parâmetro */
   if (argc == 3) {        
      r = atoi(argv[1]);
      c = atoi(argv[2]);
   }

   /* lê a matriz a partir de um arquivo de entrada */   
   int **matrix = read_matrix_from_file("data_matriz_100_200.in", &r, &c);
   #ifdef DEBUG
      printf("%dx%d\n", r, c);
      print_matrix(matrix, r, c);
   #endif

   test_passed(matrix != NULL, "Matriz lida com sucesso", "Falha ao ler a matrix");

   int r2 = M, c2 = N;
   /* gera uma matrix rxc e popula com valores pseudoaleatorios */
   int **matrix2 = create_matrix(r2, c2);
   srand(time(NULL));   // inicializa o gerador com uma semente.
   generate_elements(matrix2, r2, c2, 99);

   test_passed(matrix2 != NULL, "Matriz gerada com sucesso", "Falha ao gerar a matrix");
   #ifdef DEBUG
      printf("%dx%d\n", r2, c2);
      print_matrix(matrix2, r2, c2);
   #endif

   char filename[100];
   sprintf(filename, "data_matriz_%dx%d.in", r2, c2);
   int escreveu = write_matrix_to_file(filename, matrix2, r2, c2);
   test_passed(escreveu == 0, "Matriz escrita com sucesso", "Falha ao escrever a matrix");  

   return 0; 
} 

void test_passed(bool condition, char *success_message, char *failure_message) {
   if (condition) {
      printf("[PASSED]: %s\n", success_message);
   } else {
      printf("[FAIL]: %s\n", failure_message);
   }
}
