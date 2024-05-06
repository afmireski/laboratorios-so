#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define CONFIG_FILE "config.txt"

// Estrutura para armazenar os atributos de configuração
struct Config {
    char default_dir[100];
    char owner[50];
    // Adicione outros atributos necessários aqui
};

struct Config config; // Variável global para armazenar os atributos de configuração

// Função para ler os atributos de configuração do arquivo
void read_config() {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        perror("Error opening config file");
        exit(EXIT_FAILURE);
    }

    // Lê os atributos do arquivo e armazena na estrutura config
    fscanf(file, "%s %s", config.default_dir, config.owner);
    fclose(file);
}

// Função para imprimir os atributos carregados
void print_config() {
    printf("Default directory: %s\n", config.default_dir);
    printf("Owner: %s\n", config.owner);
}

// Função tratadora de sinais
void sig_handler(int signo) {
    if (signo == SIGHUP) {
        printf("Received SIGHUP signal. Reloading configuration...\n");
        read_config(); // Recarrega os atributos de configuração do arquivo
    }
}

int main(void) {
    // Associa a função tratadora de sinais
    if (signal(SIGHUP, sig_handler) == SIG_ERR) {
        perror("Can't catch SIGHUP");
        exit(EXIT_FAILURE);
    }

    // Lê os atributos de configuração do arquivo
    read_config();

    // Loop do menu
    int option;
    do {
        printf("\nMenu:\n");
        printf("1. Print configuration\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                print_config(); // Imprime os atributos de configuração
                break;
            case 2:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option\n");
        }
    } while (option != 2);

    return 0;
}
