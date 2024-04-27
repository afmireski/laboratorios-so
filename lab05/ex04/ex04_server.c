/**
 * Program: ex04.c
 * 
 * Descrição: Faça dois programas para atuarem respectivamente como cliente e servidor
 * para um serviço de tradução simples (só traduz palavras). O serviço de tradução deve
 * receber um código especificando a língua de origem e destino (use o padrão ISO 639-1) e
 * a palavra para traduzir (ex: pt-en:cachorro). Se não conseguir fazer a tradução devolve
 * ERROR:UNKNOWN, caso contrário, a tradução. Por exemplo, traduzir de pt-en (português para o inglês) a palavra cachorro, devolve dog.
 * -> Faça uma versão usando sockets UNIX e que delega o processamento para um processo
 * filho, isto é, o cliente pode continuar enviando mensagens para traduzir até que envie
 * a mensagem NO-NO como código.
 * 
 * Autor: André Felipe Mireski
 * Data: 27/04/2024
 * Data de entrega: xx/05/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h> // strcmp, strtok

int main() {
    char* pt_dictionary[6] = {"cachorro", "vermelho", "maça", "casa", "avião", ""};
    char* en_dictionary[6] = {"dog", "red", "apple", "house", "plane", ""};
    char* es_dictionary[6] = {"perro", "rojo", "maza", "casa", "avión", ""};

    char *socket_path = "./dictionary.socket"; // Pathname
    int server_socket, client_socket; // Endereços dos sockets
    ssize_t received_bytes;  // Quantidade de bytes recebidos
    struct sockaddr_un socket_address; // Endereço do socket
    char communication_buffer[100]; //Buffer de comunicação

    // Cria um UNIX socket do tipo STREAM
    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Erro ao criar socket");
        exit(-1);
    }

    /* configura endereço do socket */
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sun_family = AF_UNIX;
    strncpy(socket_address.sun_path, socket_path, sizeof(socket_address.sun_path)-1);
    unlink(socket_path);  // desvincular path

    /* mapeia o socket para o socket_path */
    if (bind(server_socket, (struct sockaddr*)&socket_address, sizeof(socket_address)) == -1) {
        perror("Erro ao realizar o bind do server");
        exit(-1);
    }

    /* configura para aguardar conexões */
    if (listen(server_socket, 5) == -1) {
        perror("Erro ao tentar configurar o listen do server");
        exit(-1);
    }

    while (1) {
        // Verifica se existe algum pedido de conexão
         if ((client_socket = accept(server_socket, NULL, NULL)) == -1) {
             perror("Erro ao realizar o accept do server");
             continue; // Segue para a próxima iteração
         }

         pid_t pid = fork();

         if (pid == 0) {
            // Se é o filho então executa o protocolo de tradução
            if (connect(client_socket, (struct sockaddr*)&socket_address, sizeof(socket_address)) == -1) {
                perror("Erro ao realizar o connect com o server");
                exit(-1);
            }

            /* lê dados enviados pelos clientes */
            received_bytes = recv(client_socket, communication_buffer, sizeof(communication_buffer), 0);

            // Houve uma falha ao ler as informações
            if (received_bytes == -1) {
                perror("Falha ao ler as informações do cliente");
                exit(-1);
            } 

            // A leitura terminou

            if (strcmp(communication_buffer, "no-no") == 0 || strlen(communication_buffer) == 0) {
                // Fecha a conexão com o cliente.
                close(client_socket);   
                // Encerra o processo filho
                exit(0);                             
            }

            char* source_language = strtok(communication_buffer, "-"); // Obtém a língua de origem
            char* destiny_language = strtok(NULL, "-"); // Obtém a língua de destino

            char* source_dictionary[6];
            if (strcmp(source_language, "pt") == 0) {
                memcpy(source_dictionary, pt_dictionary, sizeof(pt_dictionary));
            } else if (strcmp(source_language, "en") == 0) {
                memcpy(source_dictionary, en_dictionary, sizeof(en_dictionary));
            } else if (strcmp(source_language, "es") == 0) {
                memcpy(source_dictionary, es_dictionary, sizeof(es_dictionary));
            } else {
                printf("Linguagem de origem inválida\n");
                exit(-1);
            }

            char* destiny_dictionary[6];
            if (strcmp(destiny_language, "pt") == 0) {
                memcpy(destiny_dictionary, pt_dictionary, sizeof(pt_dictionary));
            } else if (strcmp(destiny_language, "en") == 0) {
                memcpy(destiny_dictionary, en_dictionary, sizeof(en_dictionary));
            } else if (strcmp(destiny_language, "es") == 0) {
                memcpy(destiny_dictionary, es_dictionary, sizeof(es_dictionary));
            } else {
                printf("Linguagem de destino inválida\n");
                exit(-1);
            }

            int i;
            for (i = 0; i < 6; i++) {
                if (strcmp(source_dictionary[i], communication_buffer) == 0) {
                    break;
                }
            }

            if (i == 5) {
                printf("Impossível realizar a tradução\n");
                exit(-1);
            }

            // Envia a tradução
            char translationBuffer[100];
            sprintf(translationBuffer, "Tradução: %s -> %s\n", source_dictionary[i], destiny_dictionary[i]);
            send(client_socket, translationBuffer, sizeof (translationBuffer), 0); /* envia dados */

            // Fecha a conexão com o cliente.
            close(client_socket);   
            // Encerra o processo filho
            exit(0); 
         }
    }
}
