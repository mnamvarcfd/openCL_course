#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <arrayfire.h>
#include <CL/cl.h>
#include <CL/cl.hpp>
#include <iostream>

class OpenCLpreparation
{

public:
	OpenCLpreparation();
	cl_device_id create_device();
	cl_context creatContext(cl_context device);
	cl_context creatContext(cl_context &device);
	cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename);
};

