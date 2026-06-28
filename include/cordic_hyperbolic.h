#ifndef CORDIC_HYPERBOLIC_H
#define CORDIC_HYPERBOLIC_H

#include "ieee_utils.h"
#include "cordic_lut.h"

void cordic_hyperbolic_rotate(DoubleIEEE *x, DoubleIEEE *y, DoubleIEEE *z, int iterations);

void cordic_hyperbolic_sinh_cosh(double angle_rad, double *sinh_out, double *cosh_out, int iterations);

#endif