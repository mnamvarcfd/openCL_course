#pragma once
#include "OpenCLpreparation.h"
#include "pureCppFunc.h"

class ShiftArray
{
    OpenCLpreparation OCLpreparation;

    unsigned int ARRAY_SIZE;
    int lengt;

    // Host input vectors
    double* h_a;
    double* h_b;
    // Host output vector
    double* h_c;

    // Device input buffers
    cl_mem d_a;
    cl_mem d_b;
    // Device output buffer
    cl_mem d_c;

    ////cl_platform_id cpPlatform;        // OpenCL platform
    cl_device_id device;           // device ID
    cl_context context;               // context
    cl_command_queue queue;           // command queue
    cl_program program;               // program
    cl_kernel kernel;                 // kernel

    size_t globalSize, localSize;
    cl_int err;
    size_t bytes;

public:
	ShiftArray();
	void mainFunc();
};

