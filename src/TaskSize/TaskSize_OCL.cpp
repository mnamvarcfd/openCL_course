#include "TaskSize_OCL.h"

TaskSize_OCL::TaskSize_OCL():TaskSize() {

    
    OCL = OCLib(0, 0, "E:/openCL_course/src/TaskSize/TaskSize.cl", { "Comput" });
   
    h_a = a;

    d_a = OCL.newDoubleArrayReadWrit(arraySize);

    OCL.host2Device(d_a, h_a, arraySize);
}

void TaskSize_OCL::mainFunc(){
    
    OCL.kernelExecut("Comput", arraySize, {},  {}, { d_a }, {});

}

void TaskSize_OCL::get_a(double* Arr) {

    // Read the results from the device
    OCL.device2Host(d_a, h_a, arraySize);

    for (int i = 0; i < arraySize; i++) {
        Arr[i] = h_a[i];
    }
}

TaskSize_OCL::~TaskSize_OCL() {
    clReleaseMemObject(d_a);
}


