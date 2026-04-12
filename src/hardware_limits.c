#include <stdio.h>
#include <float.h>

int main() {
    printf("--- LIMITES DE PRECISAO DA MAQUINA ---\n\n");
    
    // FLT_DIG e DBL_DIG mostram o número exato de casas decimais seguras
    printf("FLOAT  garante: %d casas decimais.\n", FLT_DIG);
    printf("DOUBLE garante: %d casas decimais.\n\n", DBL_DIG);

    // EPSILON é o menor numero que, somado a 1.0, faz diferença na máquina
    printf("O menor incremento (Epsilon) do FLOAT é: %.10e\n", FLT_EPSILON);
    printf("O menor incremento (Epsilon) do DOUBLE é: %.20e\n", DBL_EPSILON);
    
    return 0;
}
