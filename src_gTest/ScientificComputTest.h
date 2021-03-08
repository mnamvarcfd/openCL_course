#include "E:/openCL_course/src/ScientificComput.h"
#include "E:/openCL_course/src/ScientificComput_OCL.h"

#include "gtest/gtest.h"
#include <iostream>
#include <CL/cl.h>
#include <CL/cl.hpp>

class ScientificComputTest :public testing::TestWithParam<int> {

protected:
	ScientificComput objCpp;
	
	unsigned int arraySize;
	double* A;
	double* C;
	unsigned int* intA;


public:
	ScientificComputTest();
	~ScientificComputTest();
	void SetUp() override;     // gtest construction
	void TearDown() override;  // gtest destruction


};


