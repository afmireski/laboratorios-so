#include <stdio.h>
#include <string.h>

int main() {
    // Lendo a string do pipe
    char input[100];
    fgets(input, sizeof(input), stdin);

    // Calculando informações sobre a string
    int length = strlen(input) - 1; // Desconsiderando o caractere de nova linha
    int vowels = 0, consonants = 0, spaces = 0;

    for (int i = 0; i < length; i++) {
        char ch = input[i];

        if (ch == ' ') {
            spaces++;
        } else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
                ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
                vowels++;
            } else {
                consonants++;
            }
        }
    }

    // Exibindo informações sobre a string
    printf("String: %s", input);
    printf("Tamanho: %d\n", length);
    printf("Número de consoantes: %d\n", consonants);
    printf("Número de vogais: %d\n", vowels);
    printf("Número de espaços: %d\n", spaces);

    return 0;
}
