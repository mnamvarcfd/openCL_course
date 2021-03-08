#pragma once
#include "MixDoubleIntArray.h"
#include "../../Code/OCLib.h"

class MixDoubleIntArray_OCL :
    public MixDoubleIntArray
{
    OCLib OCL;

    double* h_fVal;
    //unsigned int* h_PDFpt;
    cl_mem d_fVal;
    //cl_mem d_PDFpt;

public:
	MixDoubleIntArray_OCL();
    ~MixDoubleIntArray_OCL();
	void mainFunc();
};

