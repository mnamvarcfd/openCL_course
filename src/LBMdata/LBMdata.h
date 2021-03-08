#pragma once
class LBMdata
{

public:
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
    LBMdata();
    void init();
    void get_sR(double* Arr);
    void get_sU(double* Arr);
    void get_sV(double* Arr);
    void get_R(double* Arr);
    void get_U(double* Arr);
    void get_V(double* Arr);
    void get_fVal(double* Arr);
    void indirectAdressing();
    void macroCal();
    void collision();
    void macroFinal();
    void readWriteData();
    ~LBMdata();
	void mainFunc();
};



