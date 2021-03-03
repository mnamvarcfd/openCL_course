#include "MultiKernel_OCL.h"


MultiKernel_OCL::MultiKernel_OCL():MultiKernel() {

    const char* filename = "MultiKernel.cl";


    std::vector<const char*> kernelNames;
    kernelNames.push_back("kernel1");
    kernelNames.push_back("kernel2");


   
    OCLpreparation = OCLib(0, 0, filename, kernelNames);

	
    localSize = OCLpreparation.localSize;
    globalSize = ceil(ARRAY_SIZE / (float)localSize) * localSize;



    h_a = a;

    d_a = OCLpreparation.newDoubleArrayReadWrit(ARRAY_SIZE);

    OCLpreparation.host2Device(d_a, h_a, ARRAY_SIZE);
}

void MultiKernel_OCL::mainFunc(){
    

	
    OCLpreparation.kernelExecut("kernel1", { globalSize, ARRAY_SIZE }, { d_a });

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



    OCLpreparation.kernelExecut("kernel2", { globalSize, ARRAY_SIZE }, { d_a });

    OCLpreparation.device2Host(d_a, h_a, ARRAY_SIZE);


	
    for (int i = 0; i < ARRAY_SIZE; i++) {
        //printf("val: %f\n", h_a[i]);
        if (abs(h_a[i] - 1024) > 0.001) {
            printf("Test failed\n");
            exit;
        }
    }
    printf("Test passed\n");
	
}

MultiKernel_OCL::~MultiKernel_OCL() {
    // release OpenCL resources
    clReleaseMemObject(d_a);
    //clReleaseProgram(program);
    //clReleaseKernel(kernel);
    //clReleaseCommandQueue(queue);
    //clReleaseContext(context);
}


