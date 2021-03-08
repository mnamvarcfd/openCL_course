#pragma once
class LBMdata
{

protected:
    unsigned int nNode;
    unsigned int nPDF;

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
    LBMdata();
    ~LBMdata();
	void mainFunc();
};



