# Instruções EX01 - analizador de string

## Enunciado 
 
 Faça um programa que lê strings digitadas pelo usuário e envia para outro programa que recebe
essas strings e exibe na tela: a string, o tamanho, o número de consoantes, o número de vogais e o
número de espaços.

## Execução
Compilação
Este projeto inclui um Makefile que simplifica o processo de compilação. Para compilar os programas, siga as instruções abaixo:

```bash
make

#Isso gerará os executáveis lerstringpipe e exibe_info.

#Recompilar um único programa:

make lerstringpipe
# ou
make exibe_info

#Limpar os arquivos compilados:

#Para remover os executáveis gerados, use:

make clean

#Executar o programa principal:

#Para compilar e executar o programa principal (lerstringpipe), use:
make run

#Execução Manual
#Se preferir compilar e executar manualmente, siga os passos abaixo:

#Compilar os programas:
gcc lerstringpipe.c -o lerstringpipe
gcc exibe_info.c -o exibe_info

#Executar o programa principal:
./lerstringpipe

```

Interagir com o programa:

Digite uma string: O programa solicitará que você digite uma string.
Receba a análise: O programa exibe_info será executado automaticamente e exibirá as informações sobre a string.

```bash

# Digite uma string no terminal
Digite uma string: Olá Mundo

# O programa 'exibe_info' exibirá as seguintes informações:
String: Olá Mundo
Tamanho: 9
Número de consoantes: 5
Número de vogais: 4
Número de espaços: 1
