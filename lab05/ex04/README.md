# Instruções EX04 - Servidor de Tradução

## Enunciado
Faça dois programas para atuarem respectivamente como cliente e servidor para um serviço de tradução simples (só traduz palavras). O serviço de tradução deve receber um código especificando a língua de origem e destino (use o padrão ISO 639-1) e a palavra para traduzir (ex: pt-en:cachorro). Se não conseguir fazer a tradução devolve ERROR:UNKNOWN, caso contrário, a tradução. Por exemplo, traduzir de pt-en (português para o inglês) a palavra cachorro, devolve dog.  
Faça uma versão usando sockets UNIX e que delega o processamento para um processo filho, isto é, o cliente pode continuar enviando mensagens para traduzir até que envie a mensagem NO-NO como código.

## Execução

```bash
# Compile o cliente e o servidor
make

# Se precisar recompilar:
make clean

# Subir o server
make server

# Subir o client
make client # É possível subir mais de um cliente ao mesmo tempo

```
O servidor de tradução possuí suporte a 5 palavras, nas linguagens português, inglês e espanhol:
- `pt:` cachorro, vermelho, morango, casa, barco
- `en:` dog, red, strawberry, house, boat
- `es:` perro, rojo, fresa, casa, barco

O fluxo de execução é o seguinte:

```bash
# Solicita a tradução de uma palavra, por exemplo dog (inglês), para espanhol
en-es:dog

# ...Servidor deve responder com perro

# Caso seja informada uma palavra que não existe o servidor avisará que não foi possível traduzir.
# Caso seja solicitado uma linguagem não cadastrada, o servidor avisará

# Caso o cliente deseje encerrar a conexão:
no-no

```

