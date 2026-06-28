#include <stddef.h>
#include "cordic_circular.h"

void cordic_circular_rotate(DoubleIEEE *x, DoubleIEEE *y, DoubleIEEE *z, int iterations) {
    for (int i = 0; i < iterations; i++) {
        DoubleIEEE x_shift = *x;
        DoubleIEEE y_shift = *y;

        CORDIC_SHIFT_DOUBLE(x_shift, i);
        CORDIC_SHIFT_DOUBLE(y_shift, i);

        if (z->x >= 0.0) {
            x->x = x->x - y_shift.x;
            y->x = y->x + x_shift.x;
            z->x = z->x - CORDIC_CIRCULAR_LUT[i];
        } else {
            x->x = x->x + y_shift.x;
            y->x = y->x - x_shift.x;
            z->x = z->x + CORDIC_CIRCULAR_LUT[i];
        }
    }
}

void cordic_circular_sin_cos(double angle_rad, double *sin_out, double *cos_out, int iterations) {
    DoubleIEEE x, y, z;

    x.x = CORDIC_K_CIRCULAR;
    y.x = 0.0;
    z.x = angle_rad;

    cordic_circular_rotate(&x, &y, &z, iterations);

    if (cos_out != NULL) {
        *cos_out = x.x;
    }
    if (sin_out != NULL) {
        *sin_out = y.x;
    }
}