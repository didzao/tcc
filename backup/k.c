#include <stdio.h>
#include <math.h>

/**
 * Função para calcular o ganho acumulado An do algoritmo CORDIC.
 * n: número de iterações (ex: 24 para precisão baseada em Volder).
 */
double calculate_an_gain(int n) {
    double an_gain = 1.0;

    for (int i = 0; i < n; i++) {
        double current_term = sqrt(1.0 + pow(4.0, -i));
        
        an_gain *= current_term;
    }

    return an_gain;
}

int main() {
    int iterations = 24;
    double an_gain = calculate_an_gain(iterations);
    double scale_constant = 1.0 / an_gain; // K = 1 / An

    printf("Resultados para n = %d:\n", iterations);
    printf("Ganho Acumulado (An): %.15f\n", an_gain);
    printf("Constante de Escala (K): %.15f\n", scale_constant);

    return 0;
}