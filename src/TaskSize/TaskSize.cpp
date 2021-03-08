
#include "TaskSize.h"
#include <cmath>
#include <cstdio>

TaskSize::TaskSize(){

    arraySize = 10;

    a = new double[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
        a[i] = 1.0;
    }
}

void TaskSize::mainFunc(){

    for (int i = 0; i < arraySize; i++)
    {
        double val = (double)i;
        double val2 = val + 1 + 2 * val -16 * val - 6 * val - 3;
        val2 = val2 + val + 2 + 3 * val + 4 * val - 2 * val - 1;
        val2 = val2 + val + 6 + 5 * val + 6 * val - 8 * val - 4;
        val2 = val2 + val + 1 + 6 * val + 7 * val - 4 * val - 2;
        a[i] = val2;
    }

}



void TaskSize::get_a(double* Arr) {

    for (int i = 0; i < arraySize; i++) {
        Arr[i] = a[i];
    }
}


TaskSize::~TaskSize() {
    delete(a);
}