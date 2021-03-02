
#include "AddTwoVector.h"
#include "AddTwoVector_OCL.h"

#include "TaskSize.h"
#include "TaskSize_OCL.h"


int main() {
    clock_t t1, t2;
    



    //AddTwoVector objCpp = AddTwoVector();
    //AddTwoVector_OCL  objOCL = AddTwoVector_OCL();

    TaskSize objCpp = TaskSize();
    TaskSize_OCL  objOCL = TaskSize_OCL();
    

    t1 = clock();
	
    objCpp.mainFunc();

	t2 = clock();
    double CPU_tim = (double)(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "CPU tim: " << CPU_tim << std::endl;
    
    t1 = clock();

    objOCL.mainFunc();

    t2 = clock();
    double GPU_tim = (double)(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "GPU tim: " << GPU_tim << std::endl;
    

    std::cout << "Speed up: " << CPU_tim/ GPU_tim << std::endl;
	
    //////const unsigned int ARRAY_SIZE = 1000000;
    //////double *a = new double[ARRAY_SIZE];

    //////for (int i = 0; i < ARRAY_SIZE; i++)
    //////{
    //////    a[i] = (double)i;
    //////}
    //////pureCppFunc shiftCpp = pureCppFunc();

    //////clock_t t1, t2;
    //////double tim;

    //////t1 = clock();

    //////shiftCpp.shift(a, ARRAY_SIZE);

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
