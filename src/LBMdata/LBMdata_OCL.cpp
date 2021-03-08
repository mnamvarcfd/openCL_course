#include "LBMdata_OCL.h"

LBMdata_OCL::LBMdata_OCL():LBMdata() {

    OCL = OCLib(0, 0, "E:/openCL_course/src/LBMdata/LBMdata.cl", 
        { "indirectAdressing", "macroCal", "collision", "macroFinal", "readWriteData" });

    h_R = R;
    h_U = U;
    h_V = V;

    h_sR = sR;
    h_sU = sU;
    h_sV = sV;

    h_fVal = fVal;
    h_PDFpt = PDFpt;
	
    d_R = OCL.newDoubleArrayReadWrit(nNode);
    d_U = OCL.newDoubleArrayReadWrit(nNode);
    d_V = OCL.newDoubleArrayReadWrit(nNode);
	
    d_sR = OCL.newDoubleArrayReadWrit(nNode);
    d_sU = OCL.newDoubleArrayReadWrit(nNode);
    d_sV = OCL.newDoubleArrayReadWrit(nNode);

    d_fVal = OCL.newDoubleArrayReadWrit(nPDF);
    d_PDFpt = OCL.newIntArrayRead(nPDF);


    OCL.host2Device(d_R, h_R, nNode);
    OCL.host2Device(d_U, h_U, nNode);
    OCL.host2Device(d_V, h_V, nNode);

    OCL.host2Device(d_sR, h_sR, nNode);
    OCL.host2Device(d_sU, h_sU, nNode);
    OCL.host2Device(d_sV, h_sV, nNode);

    OCL.host2Device(d_fVal, h_fVal, nPDF);

    OCL.host2DeviceInt(d_PDFpt, h_PDFpt, nPDF);

}

LBMdata_OCL::~LBMdata_OCL() {
    // release OpenCL resources
    //clReleaseMemObject(d_a);
    //clReleaseProgram(program);
    //clReleaseKernel(kernel);
    //clReleaseCommandQueue(queue);
    //clReleaseContext(context);
}


void LBMdata_OCL::get_sR(double* Arr) {
    OCL.device2Host(d_sR, h_sR, nNode);
    for (int i = 0; i < nNode; i++) {
        Arr[i] = h_sR[i];
    }
}

void LBMdata_OCL::get_sU(double* Arr) {
    OCL.device2Host(d_sU, h_sU, nNode);
    for (int i = 0; i < nNode; i++) {
        Arr[i] = h_sU[i];
    }
}

void LBMdata_OCL::get_sV(double* Arr) {
    OCL.device2Host(d_sV, h_sV, nNode);
    for (int i = 0; i < nNode; i++) {
        Arr[i] = h_sV[i];
    }
}

void LBMdata_OCL::get_R(double* Arr) {
    OCL.device2Host(d_R, h_R, nNode);
    for (int i = 0; i < nNode; i++) {
        Arr[i] = h_R[i];
    }
}

void LBMdata_OCL::get_U(double* Arr) {
    OCL.device2Host(d_U, h_U, nNode);
    for (int i = 0; i < nNode; i++) {
        Arr[i] = h_U[i];
    }
}

void LBMdata_OCL::get_V(double* Arr) {
    OCL.device2Host(d_V, h_V, nNode);
    for (int i = 0; i < nNode; i++) {
        Arr[i] = h_V[i];
    }
}

void LBMdata_OCL::get_fVal(double* Arr) {
    OCL.device2Host(d_fVal, h_fVal, nPDF);
    for (int i = 0; i < nPDF; i++) {
        Arr[i] = h_fVal[i];
    }
}



void LBMdata_OCL::indirectAdressing(){

    for (unsigned int k = 0; k < nVec; k++)
    {
        OCL.kernelExecut("indirectAdressing", nNode, {k}, {}, { d_fVal }, { d_PDFpt });
    }
	
    double* fi = new double[nPDF];
    get_fVal(fi);

    for (int i = 0; i < nPDF; i++) {
        std::cout << "fi: " << fi[i] << std::endl;
    }
    
	
}

void LBMdata_OCL::macroCal() {

    for (unsigned int k = 0; k < nVec; k++)
    {
        OCL.kernelExecut("macroCal", nNode, { k }, {},
            { d_sR, d_sU, d_sV, d_fVal }, { d_PDFpt });
    }

    //double* fi = new double[nNode];
    //get_sR(fi);

    //for (int i = 0; i < nNode; i++) {
    //    std::cout << "fi: " << fi[i] << std::endl;
    //}

}

void LBMdata_OCL::collision() {

    for (unsigned int k = 0; k < nVec; k++)
    {
        OCL.kernelExecut("collision", nNode, { k},
            {}, { d_R, d_U, d_V, d_fVal }, { d_PDFpt });
    }

    double* fi = new double[nPDF];
    get_fVal(fi);

    for (int i = 0; i < nPDF; i++) {
        std::cout << "fi: " << fi[i] << std::endl;
    }

}

void LBMdata_OCL::macroFinal() {

    OCL.kernelExecut("macroFinal", nNode, {},
        {}, { d_sR, d_sU, d_sV, d_R, d_U, d_V }, {});
}


void LBMdata_OCL::readWriteData() {

    for (unsigned int k = 0; k < nVec; k++)
    {
        OCL.kernelExecut("readWriteData", nNode, { k },
            {}, { d_sR, d_sU, d_sV, d_R, d_U, d_V, d_fVal }, { d_PDFpt });
    }

}











