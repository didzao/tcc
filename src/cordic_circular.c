#include <stddef.h>
#include <math.h>
#include "cordic_circular.h"

/* Motor 1: Modo de Rotação (força z -> 0) */
CordicVector cordic_circular_rotate(CordicVector v, int iterations) {
    for (int i = 0; i < iterations; i++) {
        DoubleIEEE x_shift = v.x;
        DoubleIEEE y_shift = v.y;

        CORDIC_SHIFT_DOUBLE(x_shift, i);
        CORDIC_SHIFT_DOUBLE(y_shift, i);

        if (v.z.x >= 0.0) {
            v.x.x = v.x.x - y_shift.x;
            v.y.x = v.y.x + x_shift.x;
            v.z.x = v.z.x - CORDIC_CIRCULAR_LUT[i];
        } else {
            v.x.x = v.x.x + y_shift.x;
            v.y.x = v.y.x - x_shift.x;
            v.z.x = v.z.x + CORDIC_CIRCULAR_LUT[i];
        }
    }
    return v;
}

/*
 * MODO DE VETORIZACAO (Circular Vectoring Mode):
 * 
 * Objetivo: Forcar a coordenada 'y' a convergir para zero (y -> 0),
 * alinhando o vetor (x, y) sobre o eixo horizontal X.
 * 
 * Intuicao Geometrica:
 * - Se y < 0: o vetor esta abaixo do eixo X -> rotaciona no sentido anti-horario (+).
 * - Se y >= 0: o vetor esta acima do eixo X -> rotaciona no sentido horario (-).
 * 
 * A cada microrrotacao corretiva, o angulo aplicado e acumulado em 'z'.
 * Ao final das iteracoes:
 *   - y_final -> 0
 *   - z_final -> z_0 + arctan(y_0 / x_0)
 *   - x_final -> (1/K) * sqrt(x_0^2 + y_0^2)   [magnitude/modulo]
 * 
 * Aplicacao para arctan(a):
 *   Configurando (x=1.0, y=a, z=0.0), z_final converge exatamente para arctan(a).
 */
CordicVector cordic_circular_vector(CordicVector v, int iterations) {
    for (int i = 0; i < iterations; i++) {
        DoubleIEEE x_shift = v.x;
        DoubleIEEE y_shift = v.y;

        CORDIC_SHIFT_DOUBLE(x_shift, i);
        CORDIC_SHIFT_DOUBLE(y_shift, i);

        /* Se y < 0, rotaciona no sentido anti-horário (d_i = +1) para aproximar de zero */
        if (v.y.x < 0.0) {
            v.x.x = v.x.x - y_shift.x;
            v.y.x = v.y.x + x_shift.x;
            v.z.x = v.z.x - CORDIC_CIRCULAR_LUT[i];
        } else {
            v.x.x = v.x.x + y_shift.x;
            v.y.x = v.y.x - x_shift.x;
            v.z.x = v.z.x + CORDIC_CIRCULAR_LUT[i];
        }
    }
    return v;
}

/* Seno e Cosseno simultâneos via Rotação */
void cordic_circular_sin_cos(double angle_rad, double *sin_out, double *cos_out, int iterations) {
    CordicVector v;
    v.x.x = CORDIC_K_CIRCULAR;
    v.y.x = 0.0;
    v.z.x = angle_rad;

    CordicVector result = cordic_circular_rotate(v, iterations);

    if (cos_out != NULL) {
        *cos_out = result.x.x;
    }
    if (sin_out != NULL) {
        *sin_out = result.y.x;
    }
}

/* Tangente: sin(x) / cos(x) */
double cordic_circular_tan(double angle_rad, int iterations) {
    double s, c;
    cordic_circular_sin_cos(angle_rad, &s, &c, iterations);

    if (fabs(c) < 1e-15) {
        return (s >= 0.0) ? INFINITY : -INFINITY;
    }

    return s / c;
}

/* Arco-tangente via Vetorização: atan(a) */
double cordic_circular_atan(double value, int iterations) {
    CordicVector v;
    v.x.x = 1.0;
    v.y.x = value;
    v.z.x = 0.0;

    CordicVector result = cordic_circular_vector(v, iterations);

    /* O valor do ângulo acumulado em z corresponde ao arco-tangente */
    return result.z.x;
}