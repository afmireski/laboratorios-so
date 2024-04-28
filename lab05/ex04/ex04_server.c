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

int main()
{
    char *pt_dictionary[6] = {"cachorro", "vermelho", "morango", "casa", "barco", ""};
    char *en_dictionary[6] = {"dog", "red", "strawberry", "house", "boat", ""};
    char *es_dictionary[6] = {"perro", "rojo", "fresa", "casa", "barco", ""};

    char *socket_path = "./dictionary.socket"; // Pathname
    int server_socket, client_socket;          // Endereços dos sockets
    ssize_t received_bytes;                    // Quantidade de bytes recebidos
    struct sockaddr_un socket_address;         // Endereço do socket
    char communication_buffer[100];            // Buffer de comunicação

    // Cria um UNIX socket do tipo STREAM
    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("Erro ao criar socket");
        exit(-1);
    }

    /* configura endereço do socket */
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sun_family = AF_UNIX;
    strncpy(socket_address.sun_path, socket_path, sizeof(socket_address.sun_path) - 1);
    unlink(socket_path); // desvincular path

    printf("Servidor de Tradução rodando....\n\n");

    /* mapeia o socket para o socket_path */
    if (bind(server_socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) == -1)
    {
        perror("Erro ao realizar o bind do server");
        exit(-1);
    }

    /* configura para aguardar conexões */
    if (listen(server_socket, 5) == -1)
    {
        perror("Erro ao tentar configurar o listen do server");
        exit(-1);
    }

    while (1)
    {
        // Verifica se existe algum pedido de conexão
        printf("Servidor - %d\n", getpid());
        if ((client_socket = accept(server_socket, NULL, NULL)) == -1)
        {
            perror("Erro ao realizar o accept do server");
            continue; // Segue para a próxima iteração
        }

        pid_t pid = fork();

        if (pid == 0)
        {
            while (1)
            {
                printf("Filho - %d\n", getpid());
                // Se é o filho então executa o protocolo de tradução

                /* lê dados enviados pelos clientes */
                received_bytes = recv(client_socket, communication_buffer, sizeof(communication_buffer), 0);

                // Houve uma falha ao ler as informações
                if (received_bytes == -1)
                {
                    perror("Falha ao ler as informações do cliente\n");
                    exit(-1);
                }

                // A leitura terminou
                // Obtém o comando de tradução
                char *translation_command = strtok(communication_buffer, ":");
                char *word = strtok(NULL, ":"); // Obtém a palavra a ser traduzida.

                printf("Comp -> %d\n", strncmp(translation_command, "no-no", 5));
                if (strncmp(translation_command, "no-no", 5) == 0 || strlen(translation_command) == 0)
                {
                    printf("Conexão encerrada1\n");
                    // Fecha a conexão com o cliente.
                    close(client_socket);
                    // Encerra o processo filho
                    exit(0);
                }

                char *source_language = strtok(translation_command, "-"); // Obtém a língua de origem
                char *destiny_language = strtok(NULL, "-");               // Obtém a língua de destino

                printf("Tradução: %s -> %s\n", source_language, destiny_language);

                char *source_dictionary[6];
                if (strncmp(source_language, "pt", 2) == 0)
                {
                    memcpy(source_dictionary, pt_dictionary, sizeof(pt_dictionary));
                }
                else if (strncmp(source_language, "en", 2) == 0)
                {
                    memcpy(source_dictionary, en_dictionary, sizeof(en_dictionary));
                }
                else if (strncmp(source_language, "es", 2) == 0)
                {
                    memcpy(source_dictionary, es_dictionary, sizeof(es_dictionary));
                }
                else
                {
                    char* error_message = "Linguagem de origem inválida\n";
                    send(client_socket, error_message, sizeof(error_message), 0); /* envia dados */
                    continue;
                }

                char *destiny_dictionary[6];
                if (strcmp(destiny_language, "pt") == 0)
                {
                    memcpy(destiny_dictionary, pt_dictionary, sizeof(pt_dictionary));
                }
                else if (strcmp(destiny_language, "en") == 0)
                {
                    memcpy(destiny_dictionary, en_dictionary, sizeof(en_dictionary));
                }
                else if (strcmp(destiny_language, "es") == 0)
                {
                    memcpy(destiny_dictionary, es_dictionary, sizeof(es_dictionary));
                }
                else
                {
                    char* error_message = "Linguagem de destino inválida\n";
                    send(client_socket, error_message, sizeof(error_message), 0); /* envia dados */
                    continue;
                }

                int i;
                for (i = 0; i < 6; i++)
                {
                    printf("%s | %s\n", source_dictionary[i], word);
                    printf("Comp -> %d\n", strncmp(source_dictionary[i], word, sizeof(source_dictionary[i])));
                    if (strncmp(source_dictionary[i], word, sizeof(source_dictionary[i])) == 0)
                    {
                        printf("Correspondência encontrada\n");
                        break;
                    }
                }

                char translation_buffer[100];
                if (i == 6)
                {
                    char* error_message = "Impossível realizar a tradução\n";
                    strcpy(translation_buffer, error_message);
                } else {
                    // Envia a tradução
                    sprintf(translation_buffer, "Tradução: %s -> %s\n", source_dictionary[i], destiny_dictionary[i]);
                }
                send(client_socket, translation_buffer, sizeof(translation_buffer), 0); /* envia dados */
                memset(communication_buffer, 0, sizeof(communication_buffer)); // Limpa o buffer
            }
        }
    }

    return 0;
}
