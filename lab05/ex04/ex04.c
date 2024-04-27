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

int main() {
    char* ptDictionary[5] = {"cachorro", "vermelho", "maça", "casa", "avião"};
    char* enDictionary[5] = {"dog", "red", "apple", "house", "plane"};
    char* esDictionary[5] = {"perro", "rojo", "maza", "casa", "avión"};
}
