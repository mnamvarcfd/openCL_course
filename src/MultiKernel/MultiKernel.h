#pragma once
class MultiKernel
{

public:
    unsigned int arraySize;

    double* a;

public:
	MultiKernel();
    ~MultiKernel();
    void mainFunc1();
    void mainFunc2();
    void get_a(double* Arr);
};



