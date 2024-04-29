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
 * Data de entrega: 05/05/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h> // strcmp, strtok

int main()
{
    char *socket_path = "./dictionary.socket"; // Pathname
    int client_socket;                         // Endereços dos sockets
    ssize_t sent_bytes;                        // Quantidade de bytes enviados
    struct sockaddr_un socket_address;         // Endereço do socket
    char communication_buffer[100];            // Buffer de comunicação

    // Cria um UNIX socket do tipo STREAM
    if ((client_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("Erro ao criar socket");
        exit(-1);
    }

    /* configura endereço do socket */
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sun_family = AF_UNIX;
    strncpy(socket_address.sun_path, socket_path, sizeof(socket_address.sun_path) - 1);

    /* mapeia o socket para o socket_path */
    if (connect(client_socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) == -1)
    {
        perror("Erro ao realizar o connect com o server");
        exit(-1);
    }

    while (1)
    {
        printf("Cliente:\n");

        /* lê dados do terminal e envia via sockets */
        while ((sent_bytes = read(STDIN_FILENO, communication_buffer, sizeof(communication_buffer))) > 0)
        {
            if (write(client_socket, communication_buffer, sent_bytes) != sent_bytes)
            {
                if (sent_bytes > 0)
                    fprintf(stderr, "partial write");
                else
                {
                    perror("write error");
                    exit(1);
                }
            }
            // Verifica se o cliente deseja encerrar a conexão
            else if (strncmp(communication_buffer, "no-no", 4) == 0 || strlen(communication_buffer) == 0)
            {
                printf("Encerrando cliente...\n");
                exit(0);
                return 0;
            }

            char buffer[100];
            ssize_t read_bytes;
            if ((read_bytes = recv(client_socket, buffer, sizeof(buffer), 0)) > 0)
            {
                printf("%s\n", buffer);
            }
        }

        return 0;
    }
}
