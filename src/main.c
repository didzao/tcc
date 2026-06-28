#include <stdio.h>
#include <math.h>
#include "cordic_circular.h"
#include "cordic_hyperbolic.h"

void test_circular_module(double angulo_graus) {
    double angulo_rad = angulo_graus * (PI / 180.0);
    double sin_cordic, cos_cordic;
    
    cordic_circular_sin_cos(angulo_rad, &sin_cordic, &cos_cordic, 24);
    
    double sin_math = sin(angulo_rad);
    double cos_math = cos(angulo_rad);
    
    printf("  [%.1f deg] CORDIC Sin: %.10f | math.h: %.10f | Erro: %.2e\n", 
           angulo_graus, sin_cordic, sin_math, fabs(sin_cordic - sin_math));
    printf("  [%.1f deg] CORDIC Cos: %.10f | math.h: %.10f | Erro: %.2e\n", 
           angulo_graus, cos_cordic, cos_math, fabs(cos_cordic - cos_math));
}

void test_hyperbolic_module(double valor_u) {
    double sinh_cordic, cosh_cordic;
    
    cordic_hyperbolic_sinh_cosh(valor_u, &sinh_cordic, &cosh_cordic, 24);
    
    double sinh_math = sinh(valor_u);
    double cosh_math = cosh(valor_u);
    
    printf("  [u = %.1f] CORDIC Sinh: %.10f | math.h: %.10f | Erro: %.2e\n", 
           valor_u, sinh_cordic, sinh_math, fabs(sinh_cordic - sinh_math));
    printf("  [u = %.1f] CORDIC Cosh: %.10f | math.h: %.10f | Erro: %.2e\n", 
           valor_u, cosh_cordic, cosh_math, fabs(cosh_cordic - cosh_math));
}

int main() {
    printf("==================================================================\n");
    printf("VALIDACAO DO PACOTE CORDIC MODULAR (Kernel de Precisao Double)\n");
    printf("==================================================================\n\n");
    
    printf("--- TESTANDO MÓDULO CIRCULAR ---\n");
    test_circular_module(0.0);
    test_circular_module(30.0);
    test_circular_module(45.0);
    printf("\n");
    
    printf("--- TESTANDO MÓDULO HIPERBÓLICO ---\n");
    test_hyperbolic_module(0.0);
    test_hyperbolic_module(0.5);
    test_hyperbolic_module(1.0);
    printf("==================================================================\n");
    
    return 0;
}