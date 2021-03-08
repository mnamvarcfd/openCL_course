#include "E:/openCL_course/src/TaskSize/TaskSize.h"
#include "E:/openCL_course/src/TaskSize/TaskSize_OCL.h"

#include "gtest/gtest.h"
#include <iostream>
#include <CL/cl.h>
#include <CL/cl.hpp>

class TaskSizeTest :public testing::TestWithParam<int> {

	TaskSizeTest();
	~TaskSizeTest();

public:
	void SetUp() override;     // gtest construction
	void TearDown() override;  // gtest destruction


};


