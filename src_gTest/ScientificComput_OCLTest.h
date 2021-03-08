#pragma once
#include "E:/openCL_course/src/ScientificComput_OCL.h"

#include "gtest/gtest.h"
#include <iostream>
#include <CL/cl.h>
#include <CL/cl.hpp>

class ScientificComput_OCLTest :public testing::TestWithParam<int> {

protected:
	ScientificComput_OCL obj;
	unsigned int arraySize;
	double* A;
	double* C;
	unsigned int* intA;

public:
	ScientificComput_OCLTest();
	~ScientificComput_OCLTest();
	void SetUp() override;     // gtest construction
	void TearDown() override;  // gtest destruction


};


