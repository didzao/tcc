#ifndef IEEE_UTILS_H
#define IEEE_UTILS_H

#include <math.h>

#define PI 3.14159265358979323846264   
#define E1 2.718281828459045235360287  

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

#define InvertSign(y) ((y).bits.s ^= 1)

/* * JUSTIFICATIVA DE ARQUITETURA (TCC):
 * As macros antigas MULT_NICE_NUMBER e MULT_NICE_NUMBER_NEG realizavam multiplicacoes por 
 * constantes estaticas somando valores fixos ao expoente e acumulando.
 * Para a biblioteca modular do CORDIC, essa abordagem foi descontinuada por dois motivos:
 * 1. Mudanca de Escopo (Deslocamento Puro): O CORDIC exige divisoes por potencias de 2 (2^-i) 
 * que variam dinamicamente a cada iteracao 'i'.
 * 2. Transicao para Precisao Double: Migramos o nucleo matematico para 64 bits para suportar 
 * a convergencia de ate 24 iteracoes com maior precisao de mantissa (52 bits).
 * * TRATAMENTO DE UNDERFLOW NA MACRO CORDIC_SHIFT_DOUBLE:
 * Ao aplicar deslocamentos agressivos em iteracoes altas (ex: i = 23), subtrair 'i' direto de um 
 * expoente binario pequeno causava subfluxo (underflow). Como o campo 'E' e um inteiro sem sinal, 
 * valores negativos faziam o bitwise "dar a volta", assumindo o valor maximo (2047), o que a 
 * FPU do hardware interpreta como Infinito (inf).
 * A nova macro blinda o algoritmo: caso o expoente 'E' seja menor ou igual ao shift 'i', o numero 
 * e truncado com seguranca para zero absoluto (0.0), impedindo a corrupcao da FPU e garantindo 
 * a estabilidade matematica do CORDIC hiperbolico e circular em bitwise puro.
 */

#define CORDIC_SHIFT_DOUBLE(val, i) do { \
    if ((val).bits.E > (unsigned int)(i)) { \
        (val).bits.E -= (i);             \
    } else {                             \
        (val).bits.E = 0;                \
        (val).bits.f = 0;                \
    }                                    \
} while(0)

/* * CODIGO ANTIGO DESCONTINUADO:
 * * #define MULT_NICE_NUMBER(y, w, k) do { \
 * (w).x = (y).x;                     \
 * (w).bits.E += (k);                 \
 * (w).x += (y).x;                    \
 * } while(0)
 * * #define MULT_NICE_NUMBER_NEG(y, w, k) do { \
 * (w).x = -(y).x;                        \
 * (w).bits.E += (k);                     \
 * (w).x += (y).x;                        \
 * } while(0)
 */

void print_float_components(FloatIEEE val);

#endif


/* * JUSTIFICATIVA DE ARQUITETURA (TCC):
 * As macros antigas MULT_NICE_NUMBER e MULT_NICE_NUMBER_NEG realizavam multiplicacoes por 
 * constantes estaticas (ex: 1.5 ou 0.75) somando valores fixos ao expoente e acumulando.
 * Para a biblioteca modular do CORDIC, essa abordagem foi descontinuada por dois motivos:
 * 1. Mudanca de Escopo (Deslocamento Puro): O CORDIC nao multiplica por valores fixos, mas sim
 * por potencias negativas de 2 (divisoes por 2^i) que mudam a cada iteracao 'i'.
 * 2. Transicao para Precisao Double: Migramos o nucleo matematico para 64 bits para suportar
 * a convergencia de ate 24 iteracoes com maior precisao de mantissa (52 bits).
 * * TRATAMENTO DE UNDERFLOW NA MACRO CORDIC_SHIFT_DOUBLE:
 * Ao aplicar deslocamentos agressivos em iteracoes altas (ex: i = 23), subtrair 'i' direto de um 
 * expoente binario pequeno causava subfluxo (underflow). Como o campo 'E' e um inteiro sem sinal, 
 * valores negativos faziam o bitwise "dar a volta", assumindo o valor maximo (2047), o que a 
 * FPU do hardware interpreta como Infinito (inf).
 * A nova macro blinda o algoritmo: caso o expoente 'E' seja menor ou igual ao shift 'i', o numero 
 * e truncado com seguranca para zero absoluto (0.0), impedindo a corrupcao da FPU.
 * * EXEMPLO PRATICO (CENARIO NORMAL):
 * Queremos calcular o deslocamento para i = 3 (o que equivale a dividir por 2^3, ou seja, / 8).
 * Se o valor original for 16.0 (em binario: 1.0 * 2^4, onde o expoente E = 4):
 * Ao fazer CORDIC_SHIFT_DOUBLE(val, 3), o bitwise subtrai 3 do expoente (E = 4 - 3 = 1).
 * O novo numero passa a ser 1.0 * 2^1, que e igual a 2.0 (16.0 / 8 = 2.0).
 * * EXEMPLO PRATICO (CENARIO DE SUBFLUXO EVITADO):
 * Se o valor atual for muito pequeno, com expoente E = 5, e tentarmos aplicar um shift de i = 6.
 * Subtrair 6 de 5 faria o unsigned estourar para 2047 (inf). A macro detecta que E <= i, pula a 
 * subtracao e zera o numero diretamente, mantendo a estabilidade matematica do pacote.
 */