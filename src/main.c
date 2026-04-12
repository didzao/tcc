#include <stdio.h>
#include "ieee_utils.h"

int main() {
    FloatIEEE y, w;
    int k = -1; 
    y.x = 11.0f;

    // Usando a função auxiliar definida no .c
    imprimir_componentes_float(y);

    // Teste CORDIC: 11 * 1.5 = 16.5
    MULT_NICE_NUMBER(y, w, k);
    printf("Resultado MultNiceNumber (k=-1): %f\n", w.x);

    // Teste CORDIC Negativo: 11 * 0.75 = 8.25
    k = -2;
    MULT_NICE_NUMBER_NEG(y, w, k); 
    printf("Resultado MultNiceNumberNeg (k=-2): %f\n", w.x);

    return 0;
}