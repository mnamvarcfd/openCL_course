#pragma once
#include "../../src/LBMdata/LBMdata.h"
#include "gtest/gtest.h"
#include <iostream>
#include <CL/cl.h>
#include <CL/cl.hpp>



class LBMdataTest :public testing::TestWithParam<int> {

protected:
	LBMdata objCpp;

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
	LBMdataTest();
	~LBMdataTest();
	void SetUp() override;     // gtest construction
	void TearDown() override;  // gtest destruction


};


