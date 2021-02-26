#include "pureCppFunc.h"
#include <cmath>

pureCppFunc::pureCppFunc(){}

void pureCppFunc::shift(double *a, const unsigned int n) {
    for (int i = n; i > 0; i--) {
        a[n] = a[n - 1] * ( sqrt(1.0) * sqrt(1.0) * sqrt(n/3.0) ) / sqrt(n / 3.0);
        //a[n] = sqrt(1.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
        //a[n] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[n];
     }
}