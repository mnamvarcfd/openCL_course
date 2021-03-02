#include "AddTwoVector.h"

#include <cstdio>

AddTwoVector::AddTwoVector(){

    ARRAY_SIZE = 100000000;

    a = new double[ARRAY_SIZE];
    b = new double[ARRAY_SIZE];
    c = new double[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        a[i] = 1.0;
        b[i] = 2.0;
    }
}

void AddTwoVector::mainFunc(){

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        c[i] = a[i] + b[i];
    }

	
    double sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += c[i];
        //printf("h_c:  %f\n", c[i]);
    }
    printf("final result: %f\n", sum / ARRAY_SIZE);

}


AddTwoVector::~AddTwoVector() {
    delete(a);
    delete(b);
    delete(c);
}