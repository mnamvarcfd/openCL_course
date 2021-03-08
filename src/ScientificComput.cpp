#include "ScientificComput.h"


ScientificComput::ScientificComput(){

    arraySize = 9;

    intA = new unsigned int[arraySize];
	
    A = new double[arraySize];
    B = new double[arraySize];
    C = new double[arraySize];

    initAllArrays();
}

void ScientificComput::initAllArrays() {

    for (int i = 0; i < arraySize; i++)
    {
        A[i] = 1.0;
        B[i] = 2.0;
        C[i] = 5.0;

        intA[i] = i;
    }
}

unsigned int ScientificComput::getAarySize() {
    return arraySize;
}

void ScientificComput::getA(double* Arr) {
    for (int i = 0; i < arraySize; i++) {
        Arr[i] = A[i];
    }
}

void ScientificComput::getB(double* Arr) {

    for (int i = 0; i < arraySize; i++) {
        Arr[i] = B[i];
    }
}

void ScientificComput::getC(double* Arr) {
    for (int i = 0; i < arraySize; i++) {
        Arr[i] = C[i];
    }
}

void ScientificComput::getintA(unsigned int* Arr) {

    for (int i = 0; i < arraySize; i++) {
        Arr[i] = intA[i];
    }
}

ScientificComput::~ScientificComput() {
    //delete(A);
    //delete(B);
    //delete(C);
}





void ScientificComput::initDoubleArray() {

    for (int i = 0; i < arraySize; i++)
    {
        A[i] = 9.0;
    }

}


void ScientificComput::multyplyScalarDoubleArray() {

    for (int i = 0; i < arraySize; i++)
    {
        A[i] = 2.5 * B[i];
    }

}

void ScientificComput::initIntegerArray() {

    for (int i = 0; i < arraySize; i++)
    {
        intA[i] = 9;
    }

}

void ScientificComput::addTwoArays() {

    for (int i = 0; i < arraySize; i++)
    {
        C[i] = A[i] + B[i];
    }

}

void ScientificComput::indirectAdressing() {

    for (unsigned int i = 0; i < arraySize; i++)
    {
        unsigned int pt = intA[i];
        A[pt] = 9.0;
    }

}


void ScientificComput::nestedLoop() {

    unsigned int nLoop = arraySize / 9;
    for (unsigned int k = 0; k < 9; k++)
    {
        for (unsigned int j = 0; j < nLoop; j++)
        {
            unsigned int i = k * nLoop + j;
            A[i] = 9.0;
        }
    }

}


double ScientificComput::multiplyOperation(double a, double b) {
    return (a * b);
}


void ScientificComput::multiplyTwoArays() {

    for (int i = 0; i < arraySize; i++)
    {
        C[i] = multiplyOperation(A[i], B[i]);
    }

}









void ScientificComput::workSizeFunc() {

    for (int i = 0; i < arraySize; i++)
    {
        double val = (double)i;
        double val2 = val + 1 + 2 * val - 16 * val - 6 * val - 3;
        val2 = val2 + val + 2 + 3 * val + 4 * val - 2 * val - 1;
        val2 = val2 + val + 6 + 5 * val + 6 * val - 8 * val - 4;
        val2 = val2 + val + 1 + 6 * val + 7 * val - 4 * val - 2;
        A[i] = val2;
    }

}
