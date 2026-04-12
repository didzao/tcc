#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Estrutura de união para manipulação direta dos bits de um número de precisão simples (float).
 * Permite acessar e modificar separadamente os campos definidos pelo padrão IEEE 754:
 * fração da mantissa (23 bits), expoente (8 bits) e bit de sinal (1 bit).
 */
typedef union floatIEEE{
    float x; 
    struct {
        unsigned int f : 23; 
        unsigned int E : 8;  
        unsigned int s : 1;  
    }bits;
}floatIEEE;

/*
 * Estrutura de união para manipulação direta dos bits de um número de precisão dupla (double).
 * Permite acessar os campos do padrão IEEE 754 em 64 bits:
 * fração da mantissa (52 bits), expoente (11 bits) e bit de sinal (1 bit).
 */
typedef union doubleIEEE{
    double x; 
    struct {
        unsigned long long f : 52; 
        unsigned long long E : 11; 
        unsigned long long s : 1;  
    }bits;
}doubleIEEE;

/*
 * Macros de definição de constantes matemáticas elementares.
 */
#define PI 3.14159265358979323846264   
#define E1 2.718281828459045235360287  

/*
 * Macro para a operação básica de multiplicação.
 */
#define mult(a, b) ((a)*(b))

/*
 * Macro que executa a operação w = y * (1 + 2^k).
 * Em vez de utilizar uma multiplicação em hardware, esta macro manipula diretamente 
 * o expoente no padrão IEEE 754 (somando k, o que equivale a um shift binário) e, 
 * em seguida, soma o valor original. Essa é a essência do "shift-and-add" do CORDIC.
 */
#define MultNiceNumber(y, w, k)   {w.x = y.x;     \
                                   w.bits.E += k;  \
                                   w.x += y.x; }

/*
 * Macro que executa a operação w = y * (1 - 2^k).
 * Aplica a mesma lógica de manipulação de expoente, mas inverte o sinal do valor 
 * inicial para simular a subtração geométrica do vetor.
 */
#define MultNiceNumberNeg(y, w, k)   {w.x = -y.x;       \
                                      w.bits.E += k;  \
                                      w.x += y.x; }

int main()
{
  floatIEEE y, w;
  int k = -1; 
  y.x = 11;
  
  // Imprime o valor inicial em formato de ponto flutuante padrão
  printf("\n x = %f ", y.x);
  
  // Desmembra e imprime os componentes individuais do número no padrão IEEE 754
  printf("\n s = %d ", y.bits.s);
  printf("\n E = %d ", y.bits.E);
  printf("\n f = %d ", y.bits.f);
  
  // Calcula e imprime o valor decimal da fração da mantissa isolada
  printf("\n f = %f ", (float)y.bits.f/pow(2,23) );

  // Aplica o deslocamento k = -1 (multiplicar por 0.5) e soma. Resultado esperado: 11 * 1.5 = 16.5
  MultNiceNumber(y, w, k);

  // Imprime o resultado da primeira transformação
  printf("\n w.x = %f ", w.x);

  k = -2; 

  // Aplica o deslocamento k = -2 (multiplicar por 0.25) com sinal negativo. Resultado esperado: 11 * 0.75 = 8.25
  MultNiceNumberNeg(y, w, k); 
  printf("\n w.x = %f ", w.x);

  // Calcula e imprime a raiz cúbica de -8 usando a função da biblioteca matemática para fins de teste
  printf("\n x**(1/3) = %f ", pow(-8.0, 1./3.));

  return 0;
}