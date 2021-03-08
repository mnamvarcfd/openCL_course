#include "LBMdata.h"
#include <cmath>
#include <cstdio>

LBMdata::LBMdata(){

    nNode = 10;
    nPDF = 10;

    R = new double[nNode];
    U = new double[nNode];
    V = new double[nNode];

    sR = new double[nNode];
    sU = new double[nNode];
    sV = new double[nNode];

    fVal = new double[nPDF];

    PDFpt = new unsigned int[nPDF];
	
    for (int i = 0; i < nNode; i++)
    {
        R[i] = 1.0;
        U[i] = 1.0;
        V[i] = 1.0;

        sR[i] = 0.0;
        sU[i] = 0.0;
        sV[i] = 0.0;
    }

    for (int i = 0; i < nPDF; i++)
    {
        fVal[i] = 0.0;
        PDFpt[i] = i;
    }
}

void LBMdata::mainFunc(){

    for (int i = 0; i < nNode; i++)
    {
        sR[i] += R[i];
        sU[i] += U[i];
        sV[i] += V[i];
    }

    for (int i = 0; i < nPDF; i++)
    {
        unsigned int pt = PDFpt[i];
        fVal[pt] += 1.0;
    }
	
    bool pass = true;
    for (int i = 0; i < nNode; i++) {
        if (abs((sR[i] - 1.0)) > 0.00000001) pass = false;
        if (abs((sU[i] - 1.0)) > 0.00000001) pass = false;
        if (abs((sV[i] - 1.0)) > 0.00000001) pass = false;
    }
    for (int i = 0; i < nPDF; i++) {
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


LBMdata::~LBMdata() {
    //delete(a);
}