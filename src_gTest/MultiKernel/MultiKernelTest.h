#include "E:/openCL_course/src/MultiKernel/MultiKernel.h"
#include "E:/openCL_course/src/MultiKernel/MultiKernel_OCL.h"

#include "gtest/gtest.h"
#include <iostream>
#include <CL/cl.h>
#include <CL/cl.hpp>

class MultiKernelTest :public testing::TestWithParam<int> {

	MultiKernelTest();
	~MultiKernelTest();

public:
	void SetUp() override;     // gtest construction
	void TearDown() override;  // gtest destruction


};


