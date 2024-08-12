# Instruções EX02 - Calculadora com Multiprogramação - Exercicio B - Pipe

## Descrição

 Faça um programa que lê uma expressão matemática simples (+, -, *, /) e passe para outro
programa que realiza o cálculo e devolve a resposta

Este projeto consiste em dois programas que trabalham juntos para ler uma expressão matemática simples (+, -, *, /) e calcular o resultado. Um programa coleta a expressão do usuário e a envia para o segundo programa, que realiza o cálculo e exibe o resultado.

### Estrutura dos Arquivos

- **envia_expressao.c:** Programa responsável por coletar a expressão matemática do usuário e enviá-la através de um pipe para outro processo.
- **realiza_calculo.c:** Programa que lê a expressão enviada através do pipe, realiza o cálculo e exibe o resultado.

## Execução

### Compilação

Para compilar os programas, utilize o `Makefile` incluído no projeto. Abra o terminal na pasta do projeto e execute:

```bash
make

#Isso gerará os executáveis envia_expressao e realiza_calculo.

#Execução dos Programas
#Para executar os programas, siga os passos abaixo:

#Execute o programa envia_expressao, que criará um pipe e solicitará ao usuário que insira uma expressão matemática:

./envia_expressao

#O programa envia_expressao criará um processo filho que executará realiza_calculo para processar a expressão.

#No terminal onde envia_expressao está rodando, digite uma expressão matemática no formato número operador número. Exemplo:

3 + 4

#O programa realiza_calculo processará a expressão recebida através do pipe e exibirá o resultado no terminal.

#Limpeza
#Para remover os executáveis gerados pela compilação, execute:

make clean

#Formato das Expressões
#As expressões devem ser fornecidas no seguinte formato:
<number1> <operator> <number2>

```

Exemplo: 10 * 3

Operadores Suportados
+ (adição)
- (subtração)
* (multiplicação)
/ (divisão)
Nota: Divisões por zero não são permitidas e resultarão em uma mensagem de erro.