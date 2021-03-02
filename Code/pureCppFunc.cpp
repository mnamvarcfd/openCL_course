#include "pureCppFunc.h"
#include <cmath>

pureCppFunc::pureCppFunc(){
}

void pureCppFunc::shift(double *a, const unsigned int n) {
    for (int i = 0; i < n; i++) {
        double val = (double)i;
        double val2 = val + 1 + 2 * val + 3 * val - 6 * val - 1;
        val2 = val2 + val + 2 + 3 * val + 4 * val - 2 * val - 3;
        val2 = val2 + val + 6 + 5 * val + 6 * val - 8 * val - 1;
        a[i] = val2 + val + 1 + 6 * val + 7 * val - 4 * val - 5; 
     }
}