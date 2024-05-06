
## Enunciado
 (First-In-First-Out). O primeiro programa, enviar_string.c, lê uma string digitada pelo usuário e a escreve em um FIFO. O segundo programa, recebe_exibe_info.c, lê a string do FIFO, analisa-a e imprime informações sobre a string, como tamanho, número de vogais, número de consoantes e número de espaços.

## Execução

```
gcc -o enviar_string enviar_string.c
gcc -o recebe_exibe_info recebe_exibe_info.c
```

Uso
Após compilar, você pode executar os programas da seguinte maneira:

Enviar String: Este programa lê uma string digitada pelo usuário e a escreve em um FIFO.

./enviar_string
Receber e Exibir Informações: Este programa lê a string do FIFO, analisa a string para contar o número de vogais, consoantes e espaços, e imprime essas informações na tela.

./recebe_exibe_info
Funcionamento
O programa enviar_string cria um FIFO nomeado (pipe) se ele não existir. Em seguida, ele abre o FIFO em modo de escrita, lê uma string digitada pelo usuário, escreve essa string no FIFO e fecha o FIFO.

O programa recebe_exibe_info abre o FIFO em modo de leitura, lê a string do FIFO, analisa a string para contar o número de vogais, consoantes e espaços e imprime essas informações na tela.

Observações
Certifique-se de que ambos os programas estão sendo executados ao mesmo tempo para que a comunicação entre eles ocorra corretamente.
Os programas podem ser encerrados usando Ctrl+C no terminal onde estão sendo executados.