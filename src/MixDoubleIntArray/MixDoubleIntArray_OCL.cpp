#include "MixDoubleIntArray_OCL.h"

MixDoubleIntArray_OCL::MixDoubleIntArray_OCL():MixDoubleIntArray() {

    OCL = OCLib(0, 0, "E:/openCL_course/src/MixDoubleIntArray/MixDoubleIntArray.cl", { "comput" });

    h_fVal = fVal;
    //h_PDFpt = PDFpt;

    d_fVal = OCL.newDoubleArrayReadWrit(nNode);
    //d_PDFpt = OCL.newIntArrayRead(nNode);

    OCL.host2Device(d_fVal, h_fVal, nNode);
    //OCL.host2Device(d_PDFpt, h_PDFpt, nNode);
}

void MixDoubleIntArray_OCL::mainFunc(){

    OCL.kernelExecut("comput", nNode, { nNode }, {}, { d_fVal }, {});

    OCL.device2Host(d_fVal, h_fVal, nNode);
	
    bool pass = true;
    for (int i = 0; i < nNode; i++) {
        std::cout << "fVal[i]: " << fVal[i] << std::endl;
        if (abs((fVal[i] - 1.0)) > 0.00000001) pass = false;
    }


    if (pass == true) {
        printf("Test passed\n");
    }
    else
    {
        printf("Test failed\n");
    }
    
}

MixDoubleIntArray_OCL::~MixDoubleIntArray_OCL() {
    //clReleaseMemObject(d_a);
    //clReleaseMemObject(d_b);
}





