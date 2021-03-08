#include "LBMdata.h"
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>

LBMdata::LBMdata(){

    nNode = 10;
    nVec = 9;
    nPDF = nNode*nVec;

    R = new double[nNode];
    U = new double[nNode];
    V = new double[nNode];

    sR = new double[nNode];
    sU = new double[nNode];
    sV = new double[nNode];

    fVal = new double[nPDF];

    PDFpt = new unsigned int[nPDF];
	
    init();
}

void LBMdata::init()
{

    for (unsigned int i = 0; i < nNode; i++)
    {
        R[i] = 1.0;
        U[i] = 0.5;
        V[i] = 0.5;

        sR[i] = 0.0;
        sU[i] = 0.0;
        sV[i] = 0.0;
    }

    for (unsigned int k = 0; k < nVec; k++)
    {
        for (unsigned int j = 0; j < nNode; j++)
        {
            unsigned int i = k * nNode + j;

            fVal[i] = k / 10.0;
            PDFpt[i] = j;
        }
    }
}

void LBMdata::get_sR(double* Arr) {
    for (int i = 0; i < nNode; i++) {
        Arr[i] = sR[i];
    }
}

void LBMdata::get_sU(double* Arr) {
    for (int i = 0; i < nNode; i++) {
        Arr[i] = sU[i];
    }
}

void LBMdata::get_sV(double* Arr) {
    for (int i = 0; i < nNode; i++) {
        Arr[i] = sV[i];
    }
}

void LBMdata::get_R(double* Arr) {
    for (int i = 0; i < nNode; i++) {
        Arr[i] = R[i];
    }
}

void LBMdata::get_U(double* Arr) {
    for (int i = 0; i < nNode; i++) {
        Arr[i] = U[i];
    }
}

void LBMdata::get_V(double* Arr) {
    for (int i = 0; i < nNode; i++) {
        Arr[i] = V[i];
    }
}

void LBMdata::get_fVal(double* Arr) {
    for (int i = 0; i < nPDF; i++) {
        Arr[i] = fVal[i];
    }
}


void LBMdata::indirectAdressing() {

    for (int i = 0; i < nPDF; i++)
    {
        unsigned int pt = PDFpt[i];
        fVal[i] = pt;
    }

}




void LBMdata::macroCal() {


    for (unsigned int k = 0; k < nVec; k++)
    {
        for (unsigned int j = 0; j < nNode; j++)
        {
            unsigned int i = k * nNode + j;

            unsigned int pt = PDFpt[i];
            sR[pt] += fVal[i];
            sU[pt] += fVal[i]*2.0;
            sV[pt] += fVal[i]*0.5;
        }
    }

}

void LBMdata::collision() {

    for (unsigned int k = 0; k < nVec; k++)
    {
        for (unsigned int j = 0; j < nNode; j++)
        {
            unsigned int i = k * nNode + j;

            unsigned int pt = PDFpt[i];
        	
            double r = R[pt];
            double u = U[pt];
            double v = V[pt];
        	
            fVal[i] += r*(u+v);
        }
    }

}

void LBMdata::macroFinal() {

    for (int i = 0; i < nNode; i++)
    {
        R[i] = sR[i]+1.0;
        U[i] = sU[i]/ R[i];
        V[i] = sV[i]/ R[i];
    }
}

void LBMdata::readWriteData(){
	
    for (unsigned int k = 0; k < nVec; k++)
    {
        for (unsigned int j = 0; j < nNode; j++)
        {
            unsigned int i = k * nNode + j;

            unsigned int pt = PDFpt[i];
        	
            sR[pt] += R[pt];
            sU[pt] += U[pt];
            sV[pt] += V[pt];

            fVal[i] += 1.0;
        }
    }
 
}


void LBMdata::mainFunc() {

    for (unsigned int k = 0; k < nVec; k++)
    {
        for (unsigned int j = 0; j < nNode; j++)
        {
            unsigned int i = k * nNode + j;

            unsigned int pt = PDFpt[i];

            sR[pt] += R[pt];
            sU[pt] += U[pt];
            sV[pt] += V[pt];

            fVal[i] += 1.0;
        }
    }

}






LBMdata::~LBMdata() {
    //delete(a);
}