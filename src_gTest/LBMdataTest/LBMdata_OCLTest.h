#pragma once
#include "../../src/LBMdata/LBMdata_OCL.h"

#include "gtest/gtest.h"
#include <iostream>
#include <CL/cl.h>
#include <CL/cl.hpp>


class LBMdata_OCLTest :public testing::TestWithParam<int> {

protected:
    LBMdata_OCL obj;

    unsigned int nNode;
    unsigned int nPDF;
    unsigned int nVec;

    double* cx;
    double* cy;
    double* wt;

    double* R;
    double* U;
    double* V;

    double* sR;
    double* sU;
    double* sV;

    double* fVal;
    unsigned int* PDFpt;

public:
	LBMdata_OCLTest();
	~LBMdata_OCLTest();
	void SetUp() override;     // gtest construction
	void TearDown() override;  // gtest destruction


};


