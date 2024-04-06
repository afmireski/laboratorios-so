#include <stdio.h>
#include <stdlib.h> // atoi
#include <string.h>
#include <stdbool.h>
#include "matriz/matriz.h"

int main(int argc, char const *argv[]){
    if (argc > 1) {
        char* filename = argv[1];

        int m, n;
        int** matrix = read_matrix_from_file(filename, &m, &n);
        if (matrix != NULL && (m > 0 || n > 0)) {
            
        }

        
    }

    return 0;
}