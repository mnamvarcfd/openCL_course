#include "AddTwoVector.h"

#include <cstdio>

AddTwoVector::AddTwoVector(){

    arraySize = 1000;

    a = new double[arraySize];
    b = new double[arraySize];
    c = new double[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
        a[i] = 1.0;
        b[i] = 2.0;
    }
}

void AddTwoVector::mainFunc(){

    for (int i = 0; i < arraySize; i++)
    {
        c[i] = a[i] + b[i];
    }

}

void AddTwoVector::get_c(double* Arr) {

    for (int i = 0; i < arraySize; i++) {
        Arr[i] = c[i];
    }
}

AddTwoVector::~AddTwoVector() {
    delete(a);
    delete(b);
    delete(c);
}