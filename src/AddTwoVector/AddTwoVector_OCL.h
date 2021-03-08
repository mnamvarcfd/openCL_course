#pragma once
#include "AddTwoVector.h"
#include "../../Code/OCLib.h"

class AddTwoVector_OCL :
    public AddTwoVector
{
    OCLib OCL;

    double* h_a;
    double* h_b;
    double* h_c;

    cl_mem d_a;
    cl_mem d_b;
    cl_mem d_c;

public:
	AddTwoVector_OCL();
    ~AddTwoVector_OCL();
	void mainFunc();
    void get_c(double* Arr);
};

