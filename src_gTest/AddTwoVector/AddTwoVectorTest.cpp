#include "AddTwoVectorTest.h"

AddTwoVectorTest::AddTwoVectorTest()
{
	std::cout << "AddTwoVectorTest" << std::endl;
}

AddTwoVectorTest::~AddTwoVectorTest()
{
	std::cout << "~AddTwoVectorTest" << std::endl;
}

void AddTwoVectorTest::SetUp()
{
	std::cout << "SetUp" << std::endl;
}

void AddTwoVectorTest::TearDown()
{
	std::cout << "TearDown" << std::endl;
}


TEST(AddTwoVectorTest, AddTwoVectorCpp) {

	AddTwoVector obj = AddTwoVector();

	obj.mainFunc();

	double* result = new double[obj.arraySize];

	obj.get_c(result);

	for (int i = 0; i < obj.arraySize; i++) {
		EXPECT_DOUBLE_EQ(result[i] , 3.0);
		printf("Result: %d  %f\n", i, result[i]);
	}

}

TEST(AddTwoVectorTest, AddTwoVectorOCL) {

	AddTwoVector_OCL obj = AddTwoVector_OCL();
	obj.mainFunc();

	double* result = new double[obj.arraySize];

	obj.get_c(result);

	for (int i = 0; i < obj.arraySize; i++) {
		EXPECT_DOUBLE_EQ(result[i], 3.0);
		printf("Result: %d  %f\n", i, result[i]);
	}

}