#include "MultiKernelTest.h"

MultiKernelTest::MultiKernelTest()
{
	std::cout << "MultiKernelTest" << std::endl;
}

MultiKernelTest::~MultiKernelTest()
{
	std::cout << "~MultiKernelTest" << std::endl;
}

void MultiKernelTest::SetUp()
{
	std::cout << "SetUp" << std::endl;
}

void MultiKernelTest::TearDown()
{
	std::cout << "TearDown" << std::endl;
}


TEST(MultiKernelTest, kernel1Cpp) {

	MultiKernel obj = MultiKernel();

	obj.mainFunc1();

	double* result = new double[obj.arraySize];

	obj.get_a(result);

	for (int i = 0; i < obj.arraySize; i++) {
		EXPECT_DOUBLE_EQ(result[i] , (double)i);
		printf("Result: %d  %f\n", i, result[i]);
	}

}

TEST(MultiKernelTest, kernel2Cpp) {

	MultiKernel obj = MultiKernel();

	obj.mainFunc2();

	double* result = new double[obj.arraySize];

	obj.get_a(result);

	for (int i = 0; i < obj.arraySize; i++) {
		EXPECT_DOUBLE_EQ(result[i], 1024.0);
		printf("Result: %d  %f\n", i, result[i]);
	}

}

TEST(MultiKernelTest, kernel1OCL) {

	MultiKernel_OCL obj = MultiKernel_OCL();

	obj.mainFunc1();

	double* result = new double[obj.arraySize];

	obj.get_a(result);

	for (int i = 0; i < obj.arraySize; i++) {
		EXPECT_DOUBLE_EQ(result[i], (double)i);
		printf("Result: %d  %f\n", i, result[i]);
	}

}


TEST(MultiKernelTest, kernel2OCL) {

	MultiKernel_OCL obj = MultiKernel_OCL();

	obj.mainFunc2();

	double* result = new double[obj.arraySize];

	obj.get_a(result);

	for (int i = 0; i < obj.arraySize; i++) {
		EXPECT_DOUBLE_EQ(result[i], 1024.0);
		printf("Result: %d  %f\n", i, result[i]);
	}

}
