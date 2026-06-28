#ifndef CORDIC_CIRCULAR_H
#define CORDIC_CIRCULAR_H

#include "ieee_utils.h"
#include "cordic_lut.h"

void cordic_circular_rotate(DoubleIEEE *x, DoubleIEEE *y, DoubleIEEE *z, int iterations);

void cordic_circular_sin_cos(double angle_rad, double *sin_out, double *cos_out, int iterations);

#endif