#include "TaskSize_OCL.h"


TaskSize_OCL::TaskSize_OCL():TaskSize() {

    const char* filename = "TaskSize.cl";
    #define KERNEL_FUNC "Comput"
    localSize = 64;

    OCLpreparation = OpenCLpreparation(0, 0, filename);

    h_a = a;

    d_a = OCLpreparation.newDoubleArrayReadWrit(ARRAY_SIZE);

    OCLpreparation.host2Device(d_a, h_a, ARRAY_SIZE);
}

void TaskSize_OCL::mainFunc(){


    //=========================================================================================
    queue = OCLpreparation.queue;
    kernel = OCLpreparation.kernel;

    // Number of total work items - localSize must be devisor
    globalSize = ceil(ARRAY_SIZE / (float)localSize) * localSize;
    std::cout << "globalSize: " << globalSize << std::endl;

    // Set the arguments to our compute kernel
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    err |= clSetKernelArg(kernel, 1, sizeof(unsigned int), &ARRAY_SIZE);


    // Execute the kernel over the entire range of the data set  
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);

    // Wait for the command queue to get serviced before reading back results
    clFinish(queue);
    //=========================================================================================



	

    // Read the results from the device
    OCLpreparation.device2Host(d_a, h_a, ARRAY_SIZE);
	
    double sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += h_a[i];
        //printf("Result: %d  %f\n", i , h_a[i]);
    }
    /*printf("final result: %f %f\n", (ARRAY_SIZE-1.0)* ARRAY_SIZE, abs((ARRAY_SIZE - 1.0) * ARRAY_SIZE - sum));*/
    if (abs((ARRAY_SIZE - 1.0) * ARRAY_SIZE - 2 * sum) < 0.00000001) {
        printf("Test passed\n");
    }
    else
    {
        printf("Test failed\n");
    }



}

TaskSize_OCL::~TaskSize_OCL() {
    // release OpenCL resources
    clReleaseMemObject(d_a);
    //clReleaseProgram(program);
    //clReleaseKernel(kernel);
    //clReleaseCommandQueue(queue);
    //clReleaseContext(context);
}


