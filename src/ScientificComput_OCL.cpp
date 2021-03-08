#include "ScientificComput_OCL.h"

ScientificComput_OCL::ScientificComput_OCL():ScientificComput() {
    
    OCL = OCLib(0, 0, "E:/openCL_course/src/ScientificComput.cl", 
        { "initDoubleArray", "initIntegerArray" , "multyplyScalarDoubleArray" ,
        "addTwoArays", "indirectAdressing", "nestedLoop", "multiplyTwoArays" } );

    h_A = A;
    h_B = B;
    h_C = C;
    h_intA = intA;

    d_A = OCL.newDoubleArrayReadWrit(arraySize);
    d_B = OCL.newDoubleArrayReadWrit(arraySize);
    d_C = OCL.newDoubleArrayReadWrit(arraySize);
    d_intA = OCL.newIntArrayReadWrit(arraySize);
	
    OCL.host2Device(d_A, h_A, arraySize);
    OCL.host2Device(d_B, h_B, arraySize);
    OCL.host2Device(d_C, h_C, arraySize);
    OCL.host2DeviceInt(d_intA, h_intA, arraySize);
}

unsigned int ScientificComput_OCL::getAarySize() {
    return arraySize;
}

void ScientificComput_OCL::getA(double* Arr) {
    OCL.device2Host(d_A, h_A, arraySize);
    for (int i = 0; i < arraySize; i++) {
        Arr[i] = h_A[i];
    }
}

void ScientificComput_OCL::getB(double* Arr) {
    OCL.device2Host(d_B, h_B, arraySize);
    for (int i = 0; i < arraySize; i++) {
        Arr[i] = h_B[i];
    }
}

void ScientificComput_OCL::getC(double* Arr) {
    OCL.device2Host(d_C, h_C, arraySize);
    for (int i = 0; i < arraySize; i++) {
        Arr[i] = h_C[i];
    }
}

void ScientificComput_OCL::getintA(unsigned int* Arr) {
    OCL.device2HostInt(d_intA, h_intA, arraySize);
    for (int i = 0; i < arraySize; i++) {
        Arr[i] = h_intA[i];
    }
}


ScientificComput_OCL::~ScientificComput_OCL() {
}





void ScientificComput_OCL::initDoubleArray() {

    OCL.kernelExecut("initDoubleArray", arraySize, {}, {}, { d_A }, {  });

}

void ScientificComput_OCL::initIntegerArray() {

    OCL.kernelExecut("initIntegerArray", arraySize, {}, {}, {}, { d_intA });

}


void ScientificComput_OCL::multyplyScalarDoubleArray() {

    OCL.kernelExecut("multyplyScalarDoubleArray", arraySize, {}, {2.5}, { d_A, d_B}, {});

}

void ScientificComput_OCL::addTwoArays() {

    OCL.kernelExecut("addTwoArays", arraySize, {}, {}, { d_A, d_B, d_C }, {});

}

void ScientificComput_OCL::indirectAdressing() {

    OCL.kernelExecut("indirectAdressing", arraySize, {}, {}, { d_A }, {d_intA});

}

void ScientificComput_OCL::nestedLoop() {

    for (unsigned int k = 0; k < 9; k++)
    {
        OCL.kernelExecut("nestedLoop", arraySize/9, {k,arraySize}, {}, { d_A }, {});
    }

}


void ScientificComput_OCL::multiplyTwoArays() {

    OCL.kernelExecut("multiplyTwoArays", arraySize, {}, {}, { d_A, d_B, d_C }, {});

}