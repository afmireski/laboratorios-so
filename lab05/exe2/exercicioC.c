#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t alarm_triggered = 0; // Variável global para indicar se o alarme foi disparado

// Função tratadora de sinais
void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("Received SIGINT signal. Starting countdown...\n");
        alarm(10); // Configura um alarme para disparar em 10 segundos
    } else if (signo == SIGALRM) {
        printf("Time's up! Exiting...\n");
        alarm_triggered = 1; // Marca que o alarme foi disparado
    }
}

int main(void) {
    // Associa a função tratadora de sinais ao sinal SIGINT
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("Can't catch SIGINT");
        exit(EXIT_FAILURE);
    }

    // Associa a função tratadora de sinais ao sinal SIGALRM
    if (signal(SIGALRM, sig_handler) == SIG_ERR) {
        perror("Can't catch SIGALRM");
        exit(EXIT_FAILURE);
    }

    // Loop para exibir a contagem regressiva enquanto o alarme não for disparado
    for (int i = 10; i >= 0 && !alarm_triggered; i--) {
        printf("%d\n", i);
        sleep(1);
    }

    return 0;
}
