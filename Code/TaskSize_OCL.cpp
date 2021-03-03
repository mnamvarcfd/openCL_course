#include "TaskSize_OCL.h"

TaskSize_OCL::TaskSize_OCL():TaskSize() {

    std::vector<const char*> kernelNames;
    kernelNames.push_back("Comput");
    
    OCLpreparation = OCLib(0, 0, "TaskSize.cl", kernelNames);

    localSize = OCLpreparation.localSize;
    globalSize = ceil(ARRAY_SIZE / (float)localSize) * localSize;

    h_a = a;

    d_a = OCLpreparation.newDoubleArrayReadWrit(ARRAY_SIZE);

    OCLpreparation.host2Device(d_a, h_a, ARRAY_SIZE);
}

void TaskSize_OCL::mainFunc(){
    
    OCLpreparation.kernelExecut("Comput", { globalSize, ARRAY_SIZE }, { d_a });

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


