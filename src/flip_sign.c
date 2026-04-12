#include <stdio.h>

typedef union floatIEEE {
    float x;
    struct {
        unsigned int f : 23;
        unsigned int E : 8;
        unsigned int s : 1;
    } bits;
} floatIEEE;

int main() {
    floatIEEE numero;

    printf("=== DEMONSTRACAO: INVERSAO DE SINAL VIA BITWISE XOR ===\n\n");

    // CENÁRIO 1: Número positivo
    numero.x = 42.5f; 
    
    printf("CENARIO 1: Numero Positivo\n");
    printf("Antes  -> Valor: %6.1f | Bit de sinal: %d\n", numero.x, numero.bits.s);

    // O operador ^= 1 (XOR) inverte apenas o bit 's'.
    // Como era 0 (positivo), 0 ^ 1 resulta em 1 (negativo).
    numero.bits.s ^= 1; 

    printf("Depois -> Valor: %6.1f | Bit de sinal: %d\n\n", numero.x, numero.bits.s);


    // CENÁRIO 2: O comportamento do Zero no IEEE 754
    numero.x = 0.0f; // Zero positivo
    
    printf("CENARIO 2: O caso do Zero (0.0)\n");
    printf("Antes  -> Valor: %6.1f | Bit de sinal: %d\n", numero.x, numero.bits.s);

    // Aplicando o XOR, o bit vira 1, gerando o famoso "zero negativo" (-0.0)
    numero.bits.s ^= 1; 

    printf("Depois -> Valor: %6.1f | Bit de sinal: %d\n\n", numero.x, numero.bits.s);

    // PROVA LÓGICA: O hardware sabe lidar com o -0.0?
    printf("CENARIO 3: Prova de equivalencia do Zero\n");
    if (numero.x == 0.0f) {
        printf("Resultado: SUCESSO! O sistema reconhece que -0.0 é matematicamente igual a 0.0\n");
    } else {
        printf("Resultado: FALHA! O sistema achou diferente.\n");
    }

    return 0;
}
