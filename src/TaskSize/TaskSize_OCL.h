#pragma once
#include "TaskSize.h"
#include "../../Code/OCLib.h"

class TaskSize_OCL :
    public TaskSize
{
    OCLib OCL;

    double* h_a;
    cl_mem d_a;

public:
	TaskSize_OCL();
	void mainFunc();
    void get_a(double* Arr);
    ~TaskSize_OCL();
};

