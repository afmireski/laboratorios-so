# Instruções para executar o cálculo da média aritmética
```bash
# Se necessário limpe o projeto
make clean

# Compile a biblioteca de matriz e o programa
make matriz && make

# Crie uma matriz de entrada executando test_matriz
## As dimensões da matriz podem ser definidas no código do programa
./test_matriz

# Execute o cálculo da média aritmética informando as dimensões da matriz
./arithmetic_average <m> <n>

# Visualize o resultado no arquivo .out
cat ./media_aritmetica_linhas_matriz_<m>x<n>.out
```