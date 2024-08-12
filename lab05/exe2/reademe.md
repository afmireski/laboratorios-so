## Instruções - Programas de Tratamento de Sinais e Configurações
# Descrição

Resolva os exercícios a seguir usando sinais:
a) Faça um programa que lê atributos de configuração de inicialização (p.   ex.:   diretório   padrão, dono,...) de um arquivo e, ao receber o signal 1 (SIGHUP), refaz a  leitura desse arquivo e modifica as variáveis internas. Para provar que funciona, faça um menu com a opção para imprimir os atributos carregados na leitura.
b) Faça um programa que manipule arquivos (ler e escrever) e que, ao receber o signal 2 (SIGINT)
ou signal 15 (SIGTERM), faça uma finalização limpa (graceful stop) –  armazenar as informações
pendentes e fechar o arquivo. 
c) Faça um programa que recebe o signal 2 (SIGINT) e dispara um alarme para  finalizar sua execução dentro de 10 segundos. Nesse intervalo, o programa deve  ficar exibindo na tela uma contagem regressiva de 1 em 1 segundo.

Este projeto contém três programas distintos que demonstram o uso de sinais e manipulação de arquivos de configuração em C. Cada programa tem uma funcionalidade específica relacionada ao tratamento de sinais ou à leitura de arquivos de configuração.

Estrutura dos Arquivos
exercicioA.c: Programa que lê um arquivo de configuração (config.txt) e permite ao usuário imprimir os atributos carregados. O programa também suporta o recarregamento das configurações ao receber o sinal SIGHUP.

exercicioB.c: Programa que escreve dados em um arquivo (data.txt) e implementa tratamento para sinais SIGINT e SIGTERM, garantindo que o arquivo seja fechado corretamente ao finalizar a execução.

exercicioC.c: Programa que implementa uma contagem regressiva ao receber o sinal SIGINT e encerra a execução após 10 segundos usando o sinal SIGALRM.

Execução
Compilação
Para compilar os programas, utilize o Makefile incluído no projeto. Abra o terminal na pasta do projeto e execute:

bash
Copiar código
make
Isso gerará os executáveis exercicioA, exercicioB e exercicioC.

Execução dos Programas
Executando exercicioA
Execute o programa:

```bash
./exercicioA
#O programa exibirá um menu com as seguintes opções:

#1. Print configuration: Imprime os atributos carregados do arquivo config.txt.
#2. Exit: Encerra o programa.
#Enquanto o programa está em execução, você pode enviar o sinal SIGHUP para recarregar as configurações do arquivo config.txt.

#Executando exercicioB
#Execute o programa:

./exercicioB
#O programa abrirá o arquivo data.txt para escrita e permanecerá em execução.

#Se desejar interromper a execução de forma segura, envie um sinal SIGINT (Ctrl+C) ou SIGTERM. O programa garantirá que o arquivo seja fechado corretamente antes de sair.

#Executando exercicioC

./exercicioC
#O programa ficará em execução, esperando pelo sinal SIGINT.

#Ao receber o sinal SIGINT (Ctrl+C), o programa iniciará uma contagem regressiva de 10 segundos. Após esse tempo, ele será encerrado automaticamente.

Limpeza
Para remover os executáveis gerados pela compilação, execute:

make clean
#Isso removerá os arquivos binários exercicioA, exercicioB, exercicioC e todos os arquivos objeto (*.o).

#Formato de Configuração (config.txt)
#O arquivo config.txt deve estar no mesmo diretório dos programas e deve seguir o seguinte formato:

<default_directory> <owner>

```

Exemplo:

arduino
Copiar código
/home/user myuser
Nota
Certifique-se de que o arquivo config.txt exista antes de executar exercicioA.
Todos os programas tratam sinais de forma robusta, garantindo um comportamento previsível ao receber sinais como SIGINT, SIGTERM e SIGHUP.