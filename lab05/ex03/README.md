# Instruções EX03 - Implementação de soma de vetores utilizando mecanismos de IPC

## Enunciado
Implemente um programa que realize a soma de vetores utilizando processos para fazer o cálculo, mas
com os vetores sendo compartilhados pelos processos. Como os espaços de memória entre os processos
são isolados, um mecanismo fornecido pelo SO deve ser usado. No caso, use memória compartilhada
para que todos os filhos operem sobre os dados, e pipes para a realização do despacho de trabalho
(intervalo de índices no vetor). O número de elementos do vetor e o número de processos filhos deve ser
fornecido pelo usuário. Por exemplo, numElementos = 1000 e numProcessos = 5, cada filho processará
200 índices; para numElementos = 1000 e numProcessos = 4, cada filho processará 250 índices.

Exemplo de soma:
<br>V1 = [1,2,3,4], V2 = [2,5,3,1], V3 = V1 + V2 = [3,7,6,5]

1. Para o desenvolvimento do trabalho, uma sugestão para o fluxo dos eventos é a seguinte:
   - Pai cria os pipes para comunicação com filhos;
   - Pai cria os filhos;
   - Pai cria (aloca) memória compartilhada
     - memória para o vetor com os dados (dados);
     - e memória para que os filhos informem o término do trabalho (sinalização);
   - Filhos bloqueiam aguardando dados no pipe;
   - Pai escreve no pipe de cada filho o intervalo em que eles devem trabalhar;
   - Filho acessa a memória compartilhada e faz o trabalho;
   - Filhos avisam pai que acabaram e encerram;
   - Pai aguarda todos acabarem, imprime o resultado e finaliza.
   
2. Para o filho, o fluxo é o seguinte:
   - Lê o pipe (bloqueia);
   - Acessa a memória compartilhada (dados) e faz o trabalho;
   - Acessa a memória compartilhada (sinalização) e escreve que acabou;
   - Filho faz limpeza e finaliza.


## Execução

```bash
# Compile o programa
make

# Se precisar recompilar:
make clean

# Executar o programa
./ex03 <numero_de_elementos> <numero_de_processos_filhos>

```

Os valores dos vetores de entrada com **n** elementos são armazenados nos arquivos _"entrada_um.out"_ e _"entrada_dois.out"_.

Os valores do resultado da soma entre os vetores são armazenados no arquivo _"resultado.out"_.
