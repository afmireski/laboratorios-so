/**
 * Autor: Alexandre Tolomeotti Enokida.
 * Data: 29/03/2024.
 * Última atualização: 30/04/2024.
*/


/**
 * find() - Procura um valor inteiro em um vetor de inteiros.
 * @*array: Valor do endereço do vetor.
 * @size: Tamanho do vetor.
 * @value: Valor para procurar no vetor.
 * @*index: Valor do endereço de uma variável para armazenar o índice caso encontre `value`.
 *
 * A função `find()` procura um valor inteiro em um vetor de inteiros. Caso encontre, armazena o índice
 * do valor encontrado em `*index` e retorna 1. Caso contrário, armazena -1 em `*index` e retorna 0.
 *
 * Return: Retorna um inteiro. `1` se encontrar o valor, `0` caso contrário.
 */
int find(int *array, int size, int value, int *index);



/**
 * distributed_search() - Procura um valor inteiro em um vetor de inteiros de forma distribuída.
 * @*ar: Valor do endereço do vetor.
 * @size: Tamanho do vetor.
 * @childs: Número de processos filhos a serem criados.
 * @value: Valor para procurar no vetor.
 *
 * A função `distributed_search()` procura um valor inteiro em um vetor de inteiros de forma distribuída.
 * A função cria processos filhos. Cada um é responsável por uma seção do vetor `*ar`. 
 * Caso encontre o valor `value`, retorna o PID do processo que encontrou o valor. Caso contrário, retorna -1.
 * A função exibe o índice no vetor onde o valor foi encontrado.
 *
 * Return: Retorna um pid_t(int). PID do processo que encontrou o valor, -1 caso contrário.
 */
pid_t distributed_search(int *array, int size, int childs, int value);