#pragma once
#include "OpenCLpreparation.h"

class Summation
{
    OpenCLpreparation OCLpreparation;

    /* OpenCL structures */
    cl_device_id device;
    cl_context context;
    cl_program program;
    cl_kernel kernel;
    cl_command_queue queue;
    cl_int i, j, err;
    size_t local_size, global_size;

    /* Data and buffers    */
    float* data;
    float sum[2], total, actual_sum;
    cl_mem input_buffer, sum_buffer;
    cl_int num_groups;

public:
	Summation();
	void mainFunc();
};

