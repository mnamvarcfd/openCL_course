#pragma once
#include "TaskSize.h"
#include "OCLib.h"

class TaskSize_OCL :
    public TaskSize
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
	TaskSize_OCL();
	void mainFunc();
    ~TaskSize_OCL();
};

