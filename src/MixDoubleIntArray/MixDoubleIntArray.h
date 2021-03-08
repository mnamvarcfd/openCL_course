#pragma once
#include <cstdio>

class MixDoubleIntArray
{

public:
    unsigned int nNode;

    double* fVal;
    unsigned int* PDFpt;

public:
	MixDoubleIntArray();
    ~MixDoubleIntArray();
	void mainFunc();
};



