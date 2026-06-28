#include <stddef.h>
#include "cordic_hyperbolic.h"

void cordic_hyperbolic_rotate(DoubleIEEE *x, DoubleIEEE *y, DoubleIEEE *z, int iterations) {
    for (int i = 1; i <= iterations; i++) {
        DoubleIEEE x_shift = *x;
        DoubleIEEE y_shift = *y;

        CORDIC_SHIFT_DOUBLE(x_shift, i);
        CORDIC_SHIFT_DOUBLE(y_shift, i);

        if (z->x >= 0.0) {
            x->x = x->x + y_shift.x;
            y->x = y->x + x_shift.x;
            z->x = z->x - CORDIC_HYPERBOLIC_LUT[i];
        } else {
            x->x = x->x - y_shift.x;
            y->x = y->x - x_shift.x;
            z->x = z->x + CORDIC_HYPERBOLIC_LUT[i];
        }

        if (i == 4 || i == 13) {
            x_shift = *x;
            y_shift = *y;

            CORDIC_SHIFT_DOUBLE(x_shift, i);
            CORDIC_SHIFT_DOUBLE(y_shift, i);

            if (z->x >= 0.0) {
                x->x = x->x + y_shift.x;
                y->x = y->x + x_shift.x;
                z->x = z->x - CORDIC_HYPERBOLIC_LUT[i];
            } else {
                x->x = x->x - y_shift.x;
                y->x = y->x - x_shift.x;
                z->x = z->x + CORDIC_HYPERBOLIC_LUT[i];
            }
        }
    }
}

void cordic_hyperbolic_sinh_cosh(double angle_rad, double *sinh_out, double *cosh_out, int iterations) {
    DoubleIEEE x, y, z;

    x.x = CORDIC_K_HYPERBOLIC;
    y.x = 0.0;
    z.x = angle_rad;

    cordic_hyperbolic_rotate(&x, &y, &z, iterations);

    if (cosh_out != NULL) {
        *cosh_out = x.x;
    }
    if (sinh_out != NULL) {
        *sinh_out = y.x;
    }
}