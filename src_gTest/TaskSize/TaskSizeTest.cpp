#include "TaskSizeTest.h"

TaskSizeTest::TaskSizeTest()
{
	std::cout << "TaskSizeTest" << std::endl;
}

TaskSizeTest::~TaskSizeTest()
{
	std::cout << "~TaskSizeTest" << std::endl;
}

void TaskSizeTest::SetUp()
{
	std::cout << "SetUp" << std::endl;
}

void TaskSizeTest::TearDown()
{
	std::cout << "TearDown" << std::endl;
}


TEST(TaskSize, TaskSizeCpp) {

	TaskSize objCpp = TaskSize();

	objCpp.mainFunc();

	double* a = new double[objCpp.arraySize];

	objCpp.get_a(a);

	for (int i = 0; i < objCpp.arraySize; i++) {
		EXPECT_DOUBLE_EQ((a[i] - i), 0.0000000);
		printf("Result: %d  %f\n", i, a[i]);
	}

}

TEST(TaskSize, TaskSizeOCL) {

	TaskSize_OCL obj = TaskSize_OCL(); 
	obj.mainFunc();

	double* a = new double[obj.arraySize];

	obj.get_a(a);

	for (int i = 0; i < obj.arraySize; i++) {
		EXPECT_DOUBLE_EQ((a[i] - i), 0.0000000);
		printf("Result: %d  %f\n", i, a[i]);
	}

}