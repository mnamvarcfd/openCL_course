#pragma once
#include "ScientificComput.h"
#include "../src/ScientificComput_OCL.h"
#include "../Code/OCLib.h"

class ScientificComput_OCL :
    public ScientificComput
{
    OCLib OCL;

    double* h_A;
    double* h_B;
    double* h_C;
    unsigned int* h_intA;
	
    cl_mem d_A;
    cl_mem d_B;
    cl_mem d_C;
    cl_mem d_intA;

public:
	ScientificComput_OCL();
    ~ScientificComput_OCL();
    void initDoubleArray();
    void initIntegerArray();
    void multyplyScalarDoubleArray();
    void addTwoArays();
    void indirectAdressing();
    void nestedLoop();
    void multiplyTwoArays();

    unsigned getAarySize();
    void getA(double* Arr);
    void getB(double* Arr);
    void getC(double* Arr);
    void getintA(unsigned int* Arr);
};

