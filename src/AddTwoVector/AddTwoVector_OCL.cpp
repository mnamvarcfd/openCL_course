#include "AddTwoVector_OCL.h"

AddTwoVector_OCL::AddTwoVector_OCL():AddTwoVector() {

    OCL = OCLib(0, 0, "E:/openCL_course/src/AddTwoVector/AddTwoVector.cl", { "vecAdd" });

    h_a = a;
    h_b = b;
    h_c = c;

    d_a = OCL.newDoubleArrayRead(arraySize);
    d_b = OCL.newDoubleArrayRead(arraySize);
    d_c = OCL.newDoubleArrayWrit(arraySize);

    OCL.host2Device(d_a, h_a, arraySize);
    OCL.host2Device(d_b, h_b, arraySize);
}

void AddTwoVector_OCL::mainFunc(){

    OCL.kernelExecut("vecAdd", arraySize, {}, {}, { d_a, d_b, d_c }, {});

}

void AddTwoVector_OCL::get_c(double* Arr) {

    OCL.device2Host(d_c, h_c, arraySize);

    for (int i = 0; i < arraySize; i++) {
        Arr[i] = h_c[i];
    }
}

AddTwoVector_OCL::~AddTwoVector_OCL() {
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
}



