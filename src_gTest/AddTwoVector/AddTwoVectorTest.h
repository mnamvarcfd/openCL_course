#include "E:/openCL_course/src/AddTwoVector/AddTwoVector.h"
#include "E:/openCL_course/src/AddTwoVector/AddTwoVector_OCL.h"

#include "gtest/gtest.h"
#include <iostream>
#include <CL/cl.h>
#include <CL/cl.hpp>

class AddTwoVectorTest :public testing::TestWithParam<int> {

	AddTwoVectorTest();
	~AddTwoVectorTest();

public:
	void SetUp() override;     // gtest construction
	void TearDown() override;  // gtest destruction


};


