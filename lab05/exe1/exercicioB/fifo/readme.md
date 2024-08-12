# Instruçõe EX02 - calculadora com multiprogramação - exercicio a - FIFO


## Descrição
 Faça um programa que lê uma expressão matemática simples (+, -, *, /) e passe para outro
programa que realiza o cálculo e devolve a resposta

envia_expressao_fifo: Solicita ao usuário uma expressão matemática e a envia através do FIFO.
realiza_calculo_fifo: Recebe a expressão matemática do FIFO, realiza o cálculo e exibe o resultado.
Estrutura dos Arquivos
envia_expressao_fifo.c: Programa responsável por coletar a expressão matemática do usuário e enviá-la via FIFO.
realiza_calculo_fifo.c: Programa que lê a expressão enviada, realiza o cálculo e exibe o resultado.

## Execução

Compilação
Para compilar os programas, utilize o Makefile incluído no projeto. Abra o terminal na pasta do projeto e execute:

```bash

make

#Isso gerará os executáveis envia_expressao_fifo e realiza_calculo_fifo.

#Para executar os programas, siga os passos abaixo:

#Abra dois terminais:

#No primeiro terminal, execute o programa realiza_calculo_fifo para aguardar a expressão matemática:

./realiza_calculo_fifo

#No segundo terminal, execute o programa envia_expressao_fifo para enviar a expressão matemática:
./envia_expressao_fifo

#Interação:

#No terminal onde envia_expressao_fifo está rodando, digite uma expressão matemática no formato: número operador número. Exemplo:

3 + 4

#O programa realiza_calculo_fifo processará a expressão e exibirá o resultado no terminal.

#Limpeza
#Para remover os executáveis gerados pela compilação, execute:

#Formato das Expressões
#As expressões devem ser fornecidas no seguinte formato:
<number1> <operator> <number2>

```

Exemplo: 10 * 3
Operadores Suportados:
+ (adição)
- (subtração)
* (multiplicação)
/ (divisão)
Nota: Divisões por zero não são permitidas e resultam em uma mensagem de erro.