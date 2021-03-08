#pragma once
#include "LBMdata.h"
#include "OCLib.h"

class LBMdata_OCL :
    public LBMdata
{
    OCLib OCL;

    double* h_cx;
    double* h_cy;
    double* h_wt;

    double* h_R;
    double* h_U;
    double* h_V;

    double* h_sR;
    double* h_sU;
    double* h_sV;

    double* h_fVal;
    unsigned int* h_PDFpt;

    cl_mem d_a;
    cl_mem d_cx;
    cl_mem d_cy;
    cl_mem d_wt;

    cl_mem d_R;
    cl_mem d_U;
    cl_mem d_V;

    cl_mem d_sR;
    cl_mem d_sU;
    cl_mem d_sV;

    cl_mem d_fVal;
    cl_mem d_PDFpt;
    
public:
	LBMdata_OCL();
    ~LBMdata_OCL();
	void mainFunc();
};

