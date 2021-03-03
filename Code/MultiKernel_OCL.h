#pragma once
#include "MultiKernel.h"
#include "OCLib.h"

class MultiKernel_OCL :
    public MultiKernel
{
    OCLib OCLpreparation;

    double* h_a;

    cl_mem d_a;


    cl_command_queue queue;           // command queue
    cl_kernel kernel;                 // kernel

    size_t globalSize, localSize;
    cl_int err;
    size_t bytes;

public:
	MultiKernel_OCL();
	void mainFunc();
    ~MultiKernel_OCL();
};

