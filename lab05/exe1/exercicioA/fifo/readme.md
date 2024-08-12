
# Instruções EX01 - analizador de string


## Enunciado
O exercicio 1 A consiste em dois programas em C que demonstram comunicação entre processos usando pipes. O primeiro programa, lerstringpipe.c, lê uma string inserida pelo usuário e a escreve em um pipe. O segundo programa, exibe_info.c, lê a string do pipe, a analisa e imprime informações sobre a string, como seu comprimento, número de vogais, número de consoantes e número de espaços.

## Execução

```bash
# Compile o programa
make

# Se precisar recompilar:
make clean

# Execute o enviar_string.c
make enviar_string

# Execute o recebe_info.c
make recebe_info # execute-o em outro terminal

```
Uso
Após compilar, você pode executar os programas da seguinte maneira:

Enviar String: Este programa lê uma string digitada pelo usuário e a escreve em um FIFO.

./enviar_string
O programa enviar_string cria um FIFO nomeado (pipe) se ele não existir. Em seguida, ele abre o FIFO em modo de escrita, lê uma string digitada pelo usuário, escreve essa string no FIFO e fecha o FIFO.

./recebe_exibe_info
Funcionamento
Receber e Exibir Informações: Este programa lê a string do FIFO, analisa a string para contar o número de vogais, consoantes e espaços, e imprime essas informações na tela.


Observações
Certifique-se de que ambos os programas estão sendo executados ao mesmo tempo para que a comunicação entre eles ocorra corretamente.
Os programas podem ser encerrados usando Ctrl+C no terminal onde estão sendo executados.