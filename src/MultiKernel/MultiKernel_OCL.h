#pragma once
#include "MultiKernel.h"
#include "../../Code/OCLib.h"

class MultiKernel_OCL :
    public MultiKernel
{
    OCLib OCL;

    double* h_a;
    cl_mem d_a;

public:
    MultiKernel_OCL();
    ~MultiKernel_OCL();;
    void mainFunc1();
    void mainFunc2();
    void get_a(double* Arr);
};

