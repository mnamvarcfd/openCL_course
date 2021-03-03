#include "AddTwoVector_OCL.h"

AddTwoVector_OCL::AddTwoVector_OCL():AddTwoVector() {

    std::vector<const char*> kernelNames = {"vecAdd"};
    OCLpreparation = OCLib(0, 0, "vecAdd.cl", kernelNames);

    localSize = OCLpreparation.localSize;
    globalSize = ceil(ARRAY_SIZE / (float)localSize) * localSize;
	
    h_a = a;
    h_b = b;
    h_c = c;

    d_a = OCLpreparation.newDoubleArrayRead(ARRAY_SIZE);
    d_b = OCLpreparation.newDoubleArrayRead(ARRAY_SIZE);
    d_c = OCLpreparation.newDoubleArrayWrit(ARRAY_SIZE);

    OCLpreparation.host2Device(d_a, h_a, ARRAY_SIZE);
    OCLpreparation.host2Device(d_b, h_b, ARRAY_SIZE);
}

void AddTwoVector_OCL::mainFunc(){

    OCLpreparation.kernelExecut("vecAdd", { globalSize, ARRAY_SIZE }, { d_a, d_b, d_c });

    // Read the results from the device
    OCLpreparation.device2Host(d_c, h_c, ARRAY_SIZE);
	
    //Sum up vector c and print result divided by ARRAY_SIZE, this should equal 1 within error
    double sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += h_c[i];
        //printf("h_c:  %f\n", h_c[i]);
    }
    printf("final result: %f\n", sum / ARRAY_SIZE);



}

AddTwoVector_OCL::~AddTwoVector_OCL() {
    // release OpenCL resources
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    //clReleaseProgram(program);
    //clReleaseKernel(kernel);
    //clReleaseCommandQueue(queue);
    //clReleaseContext(context);
}



////=========================================================================================
//queue = OCLpreparation.queue;
//kernel = OCLpreparation.kernels[0];

//// Set the arguments to our compute kernel
//err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
//err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
//err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
//err |= clSetKernelArg(kernel, 3, sizeof(unsigned int), &ARRAY_SIZE);

//// Execute the kernel over the entire range of the data set  
//err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);

//// Wait for the command queue to get serviced before reading back results
//clFinish(queue);
////=========================================================================================




