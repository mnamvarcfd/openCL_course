#include "ScientificComputTest.h"



ScientificComputTest::ScientificComputTest()
{
	std::cout << "ScientificComputTest" << std::endl;
	objCpp = ScientificComput();

	arraySize = objCpp.getAarySize();
	A = new double[arraySize];
	C = new double[arraySize];
	intA = new unsigned int[arraySize];

}

ScientificComputTest::~ScientificComputTest()
{
	std::cout << "~ScientificComputTest" << std::endl;
}

void ScientificComputTest::SetUp()
{
	std::cout << "SetUp" << std::endl;
	objCpp.initAllArrays();
}

void ScientificComputTest::TearDown()
{
	std::cout << "TearDown" << std::endl;
}


INSTANTIATE_TEST_CASE_P(implement, ScientificComputTest, ::testing::Values(0/*,1,2,3,4*/));

TEST_P(ScientificComputTest, initDoubleArray) {

	objCpp.initDoubleArray();

	objCpp.getA(A);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(A[i] , 9.0);
	}

}

TEST_P(ScientificComputTest, multyplyScalarDoubleArray) {

	objCpp.multyplyScalarDoubleArray();

	objCpp.getA(A);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(A[i], 5.0);
	}

}

TEST_P(ScientificComputTest, initIntegerArray) {

	objCpp.initIntegerArray();

	objCpp.getintA(intA);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_EQ(intA[i],9);
	}

}

TEST_P(ScientificComputTest, addTwoArays) {

	objCpp.addTwoArays();

	objCpp.getC(C);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(C[i], 3);
	}

}

TEST_P(ScientificComputTest, indirectAdressing) {

	objCpp.indirectAdressing();

	objCpp.getA(A);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(A[i], 9.0);
	}

}

TEST_P(ScientificComputTest, nestedLoop) {

	objCpp.nestedLoop();

	objCpp.getA(A);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(A[i], 9.0);
	}

}


TEST_P(ScientificComputTest, multiplyTwoArays) {

	objCpp.multiplyTwoArays();

	objCpp.getC(C);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(C[i], 2.0);
	}

}








////
////
////TEST_P(ScientificComputTest, workSizeFunc) {
////
////	objCpp.workSizeFunc();
////
////	objCpp.getA(A);
////
////	for (int i = 0; i < arraySize; i++) {
////		EXPECT_DOUBLE_EQ(A[i], (double)i);
////		printf("Result: %d  %f\n", i, A[i]);
////	}
////
////}