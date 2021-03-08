#include "LBMdata_OCL.h"

LBMdata_OCL::LBMdata_OCL():LBMdata() {

    OCL = OCLib(0, 0, "LBMdata.cl", { "Comput" });

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

    OCL.host2Device(d_PDFpt, h_PDFpt, nPDF);
}

void LBMdata_OCL::mainFunc(){
    
    //OCL.kernelExecut("Comput", nNode, { nNode }, {}, { d_R, d_U, d_V, d_sR, d_sU, d_sV, d_fVal }, { d_PDFpt });


    size_t err;

    size_t localSize = 64;
    size_t globalSize = ceil(nNode / (float)localSize) * localSize;

    err = clSetKernelArg(OCL.kernels[0], 0, sizeof(unsigned int), &nNode);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;

    err = clSetKernelArg(OCL.kernels[0], 1, sizeof(cl_mem), &d_R);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;
    err = clSetKernelArg(OCL.kernels[0], 2, sizeof(cl_mem), &d_U);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;
    err = clSetKernelArg(OCL.kernels[0], 3, sizeof(cl_mem), &d_V);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;
	
    err = clSetKernelArg(OCL.kernels[0], 4, sizeof(cl_mem), &d_sR);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;
    err = clSetKernelArg(OCL.kernels[0], 5, sizeof(cl_mem), &d_sU);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;
    err = clSetKernelArg(OCL.kernels[0], 6, sizeof(cl_mem), &d_sV);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;

    err = clSetKernelArg(OCL.kernels[0], 7, sizeof(cl_mem), &d_fVal);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;
    err = clSetKernelArg(OCL.kernels[0], 8, sizeof(cl_mem), &d_PDFpt);
    if (err < 0) std::cout << "set arg error  : " << err << std::endl;


    // Execute the kernel over the entire range of the data set  
    err = clEnqueueNDRangeKernel(OCL.queue, OCL.kernels[0], 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
    if (err < 0) std::cout << "Execute kernel error : " << err << std::endl;

    // Wait for the command queue to get serviced before reading back results
    clFinish(OCL.queue);

	
    OCL.device2Host(d_sR, h_sR, nNode);
    OCL.device2Host(d_sU, h_sU, nNode);
    OCL.device2Host(d_sV, h_sV, nNode);
    OCL.device2Host(d_fVal, h_fVal, nPDF);

	

    bool pass = true;
    for (int i = 0; i < nNode; i++) {
        if (abs((h_sR[i] - 1.0)) > 0.00000001) pass = false;
        if (abs((h_sU[i] - 1.0)) > 0.00000001) pass = false;
        if (abs((h_sV[i] - 1.0)) > 0.00000001) pass = false;
    }
    for (int i = 0; i < nPDF; i++) {
        std::cout <<i<< "  fVal  : " << fVal[i] << std::endl;
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

LBMdata_OCL::~LBMdata_OCL() {
    // release OpenCL resources
    //clReleaseMemObject(d_a);
    //clReleaseProgram(program);
    //clReleaseKernel(kernel);
    //clReleaseCommandQueue(queue);
    //clReleaseContext(context);
}


