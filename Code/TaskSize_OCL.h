#pragma once
#include "TaskSize.h"
#include "OpenCLpreparation.h"

class TaskSize_OCL :
    public TaskSize
{
    OpenCLpreparation OCLpreparation;

    double* h_a;

    // Device input buffers
    cl_mem d_a;

    cl_device_id device;           // device ID
    cl_context context;               // context
    cl_command_queue queue;           // command queue
    cl_program program;               // program
    cl_kernel kernel;                 // kernel
    char* programSource;

    size_t globalSize, localSize;
    cl_int err;
    size_t bytes;

public:
	TaskSize_OCL();
	void mainFunc();
    ~TaskSize_OCL();
};

