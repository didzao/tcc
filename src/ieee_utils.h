#ifndef IEEE_UTILS_H
#define IEEE_UTILS_H

#include <math.h>

// Definições de constantes
#define PI 3.14159265358979323846264   
#define E1 2.718281828459045235360287  

// Estruturas de união para manipulação de bits
typedef union {
    float x; 
    struct {
        unsigned int f : 23; 
        unsigned int E : 8;  
        unsigned int s : 1;  
    } bits;
} FloatIEEE;

typedef union {
    double x; 
    struct {
        unsigned long long f : 52; 
        unsigned long long E : 11; 
        unsigned long long s : 1;  
    } bits;
} DoubleIEEE;

// Macros de utilidade
#define MULT(a, b) ((a) * (b))

// Macros CORDIC (Shift-and-add)
#define MULT_NICE_NUMBER(y, w, k) do { \
    (w).x = (y).x;                     \
    (w).bits.E += (k);                 \
    (w).x += (y).x;                    \
} while(0)

#define MULT_NICE_NUMBER_NEG(y, w, k) do { \
    (w).x = -(y).x;                        \
    (w).bits.E += (k);                     \
    (w).x += (y).x;                        \
} while(0)

// Protótipo de função (exemplo se quiser transformar as macros em funções reais)
void imprimir_componentes_float(FloatIEEE val);

#endif