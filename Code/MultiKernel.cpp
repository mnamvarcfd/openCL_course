#include "MultiKernel.h"
#include <cmath>
#include <cstdio>

MultiKernel::MultiKernel(){

    ARRAY_SIZE = 1000000;

    a = new double[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        a[i] = 1.0;
    }
}

void MultiKernel::mainFunc(){

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        double val = (double)i;
        double val2 = val + 1 + 2 * val -16 * val - 6 * val - 3;
        val2 = val2 + val + 2 + 3 * val + 4 * val - 2 * val - 1;
        val2 = val2 + val + 6 + 5 * val + 6 * val - 8 * val - 4;
        val2 = val2 + val + 1 + 6 * val + 7 * val - 4 * val - 2;
        a[i] = val2;
    }

	
    double sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += a[i];
        //printf("Result: %d  %f\n", i , a[i]);
    }
    /*printf("final result: %f %f\n", (ARRAY_SIZE-1.0)* ARRAY_SIZE, abs((ARRAY_SIZE - 1.0) * ARRAY_SIZE - sum));*/
    if ( abs((ARRAY_SIZE - 1.0) * ARRAY_SIZE - 2*sum) < 0.00000001) {
        printf("Test passed\n");
    }
    else
    {
        printf("Test failed\n");
    }



	
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        a[i] = 1024;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if(abs(a[i]-1024)>0.00000001) printf("Test failed\n");
    }
	
}


MultiKernel::~MultiKernel() {
    delete(a);
}