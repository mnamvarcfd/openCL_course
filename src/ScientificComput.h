#pragma once
#include <cmath>
#include <cstdio>
class ScientificComput
{

protected:
    unsigned int arraySize;

    unsigned int* intA;
	
    double* A;
    double* B;
    double* C;

public:
	ScientificComput();
    void initAllArrays();
    void workSizeFunc();
    void addTwoArays();
    void indirectAdressing();
    void nestedLoop();
    double multiplyOperation(double a, double b);
    void multiplyTwoArays();
    double plusOperation(double a, double b);
    void initDoubleArray();
    void multyplyScalarDoubleArray();
    void initIntegerArray();
    unsigned getAarySize();
    void getA(double* Arr);
    void getC(double* Arr);
    void getintA(unsigned* Arr);
    void getB(double* Arr);
    ~ScientificComput();
    void mainFunc1();
    void mainFunc2();
    void get_a(double* Arr);
};



