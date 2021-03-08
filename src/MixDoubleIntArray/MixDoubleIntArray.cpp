#include "MixDoubleIntArray.h"
#include <cmath>

MixDoubleIntArray::MixDoubleIntArray(){

    nNode = 10;

    fVal = new double[nNode];
    PDFpt = new unsigned int[nNode];

    for (int i = 0; i < nNode; i++)
    {
        fVal[i] = 9.0;
        PDFpt[i] = i;
    }
}

void MixDoubleIntArray::mainFunc(){

    for (int i = 0; i < nNode; i++)
    {
        unsigned int pt = PDFpt[i];
        fVal[pt] = 1.0;
    }

    bool pass = true;
    for (int i = 0; i < nNode; i++) {
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

MixDoubleIntArray::~MixDoubleIntArray() {
    delete(fVal);
    delete(PDFpt);
}