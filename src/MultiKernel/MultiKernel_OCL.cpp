#include "MultiKernel_OCL.h"


MultiKernel_OCL::MultiKernel_OCL():MultiKernel() {
    
    OCL = OCLib(0, 0, "E:/openCL_course/src/MultiKernel/MultiKernel.cl", { "kernel1", "kernel2" });

    h_a = a;

    d_a = OCL.newDoubleArrayReadWrit(arraySize);

    OCL.host2Device(d_a, h_a, arraySize);
}

void MultiKernel_OCL::mainFunc1(){
    
    OCL.kernelExecut("kernel1", arraySize, { arraySize }, {}, {d_a}, {  });

}

void MultiKernel_OCL::mainFunc2() {

    OCL.kernelExecut("kernel2", arraySize, { arraySize }, {}, { d_a }, {  });

}

void MultiKernel_OCL::get_a(double* Arr) {

    OCL.device2Host(d_a, h_a, arraySize);

    for (int i = 0; i < arraySize; i++) {
        Arr[i] = a[i];
    }
}

MultiKernel_OCL::~MultiKernel_OCL() {
    clReleaseMemObject(d_a);
}


