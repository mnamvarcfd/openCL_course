#include "AddTwoVector.h"
#include "AddTwoVector_OCL.h"


#include "../src/TaskSize/TaskSize.h"
#include "../src/TaskSize/TaskSize_OCL.h"

#include "../src/MixDoubleIntArray/MixDoubleIntArray.h"
#include "../src/MixDoubleIntArray/MixDoubleIntArray_OCL.h"

#include "../src/ScientificComput.h"
#include "../src/ScientificComput_OCL.h"

#include "../src/LBMdata/LBMdata.h"
#include "../src/LBMdata/LBMdata_OCL.h"


int main() {
    clock_t t1, t2;

	
    //AddTwoVector objCpp = AddTwoVector();
    //AddTwoVector_OCL  objOCL = AddTwoVector_OCL();

    //TaskSize objCpp = TaskSize();
    //TaskSize_OCL  objOCL = TaskSize_OCL();

    //MultiKernel objCpp = MultiKernel();
    //ScientificComput_OCL  objOCL = ScientificComput_OCL();

    LBMdata objCpp = LBMdata();
    LBMdata_OCL  objOCL = LBMdata_OCL();

    //MixDoubleIntArray objCpp = MixDoubleIntArray();
    //MixDoubleIntArray_OCL  objOCL = MixDoubleIntArray_OCL();

    //ScientificComput objCpp = ScientificComput();
    //ScientificComput_OCL  objOCL = ScientificComput_OCL();
	
    t1 = clock();
	
    //objCpp.initDoubleArray();
    //objCpp.initIntegerArray();

	t2 = clock();
    double CPU_tim = (double)(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "CPU tim: " << CPU_tim << std::endl;
    
    t1 = clock();
    
    //objOCL.initDoubleArray();
    //objOCL.initIntegerArray();
    //objOCL.multyplyScalarDoubleArray();
    //objOCL.indirectAdressing();
    //objOCL.macroCal();
    objOCL.collision();
	

    t2 = clock();
    double GPU_tim = (double)(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "GPU tim: " << GPU_tim << std::endl;
    

    std::cout << "Speed up: " << CPU_tim/ GPU_tim << std::endl;
	
    //////const unsigned int arraySize = 1000000;
    //////double *a = new double[arraySize];

    //////for (int i = 0; i < arraySize; i++)
    //////{
    //////    a[i] = (double)i;
    //////}
    //////pureCppFunc shiftCpp = pureCppFunc();

    //////clock_t t1, t2;
    //////double tim;

    //////t1 = clock();

    //////shiftCpp.shift(a, arraySize);

    //////t2 = clock();
    //////tim = (double)(t2 - t1) / CLOCKS_PER_SEC;
    //////std::cout << "CPU tim: " << tim << std::endl;



    //////CompareComputPower ComputPower = CompareComputPower();
    //////t1 = clock();

    //////ComputPower.mainFunc();

    //////t2 = clock();
    //////tim = (double)(t2 - t1) / CLOCKS_PER_SEC;
    //////std::cout << "GPU tim: " << tim << std::endl;


    std::cout << "======== end of main =========" <<std::endl;
    int b;
    std::cin >> b;
    return 0;
}








