#include "ScientificComput_OCLTest.h"

ScientificComput_OCLTest::ScientificComput_OCLTest()
{
	std::cout << "ScientificComput_OCLTest" << std::endl;
	
	obj = ScientificComput_OCL();

	arraySize = obj.getAarySize();
	A = new double[arraySize];
	C = new double[arraySize];
	intA = new unsigned int[arraySize];

}

ScientificComput_OCLTest::~ScientificComput_OCLTest()
{
	std::cout << "~ScientificComput_OCLTest" << std::endl;
}

void ScientificComput_OCLTest::SetUp()
{
	std::cout << "SetUp" << std::endl;
	obj.initAllArrays();
}

void ScientificComput_OCLTest::TearDown()
{
	std::cout << "TearDown" << std::endl;
}


INSTANTIATE_TEST_CASE_P(implement, ScientificComput_OCLTest, ::testing::Values(0/*,1,2,3,4*/));

TEST_P(ScientificComput_OCLTest, initDoubleArray) {

	obj.initDoubleArray();

	obj.getA(A);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(A[i] , 9.0);
	}

}

TEST_P(ScientificComput_OCLTest, initIntegerArray) {

	obj.initIntegerArray();

	obj.getintA(intA);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_EQ(intA[i], 9);
	}

}

TEST_P(ScientificComput_OCLTest, multyplyScalarDoubleArray) {

	obj.multyplyScalarDoubleArray();

	obj.getA(A);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(A[i], 5.0);
	}

}

TEST_P(ScientificComput_OCLTest, addTwoArays) {

	obj.addTwoArays();

	obj.getC(C);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(C[i], 3.0);
	}

}

TEST_P(ScientificComput_OCLTest, indirectAdressing) {

	obj.indirectAdressing();

	obj.getA(A);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(A[i], 9.0);
	}

}

TEST_P(ScientificComput_OCLTest, nestedLoop) {

	obj.nestedLoop();

	obj.getA(A);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(A[i], 9.0);
	}

}

TEST_P(ScientificComput_OCLTest, multiplyTwoArays) {

	obj.multiplyTwoArays();

	obj.getC(C);

	for (int i = 0; i < arraySize; i++) {
		EXPECT_DOUBLE_EQ(C[i], 2.0);
	}

}





////
////TEST_P(ScientificComput_OCLTest, initIntegerArray) {
////
////	obj.initArray_intA();
////
////	obj.getintA(intA);
////
////	for (int i = 0; i < arraySize; i++) {
////		EXPECT_EQ(intA[i],9);
////		printf("Result: %d  %d\n", i, intA[i]);
////	}
////
////}
////
////TEST_P(ScientificComput_OCLTest, addTwoArays) {
////
////	obj.addTwoArays();
////
////	obj.getC(C);
////
////	for (int i = 0; i < arraySize; i++) {
////		EXPECT_DOUBLE_EQ(C[i], 3);
////		printf("Result: %d  %f\n", i, A[i]);
////	}
////
////}
////
////TEST_P(ScientificComput_OCLTest, indirectAdressing) {
////
////	obj.indirectAdressing();
////
////	obj.getA(A);
////
////	for (int i = 0; i < arraySize; i++) {
////		EXPECT_DOUBLE_EQ(A[i], 9.0);
////		printf("Result: %d  %f\n", i, A[i]);
////	}
////
////}
////
////TEST_P(ScientificComput_OCLTest, initDoubleArray_OCL) {
////
////	ScientificComput_OCL objOCL = ScientificComput_OCL();
////	//objOCL.initDoubleArray();
////
////	//objOCL.getA(A);
////
////	//for (int i = 0; i < arraySize; i++) {
////	//	EXPECT_DOUBLE_EQ(A[i], 9.0);
////	//	printf("Result: %d  %f\n", i, A[i]);
////	//}
////
////}
////
////
////
////
////TEST_P(ScientificComput_OCLTest, workSizeFunc) {
////
////	obj.workSizeFunc();
////
////	obj.getA(A);
////
////	for (int i = 0; i < arraySize; i++) {
////		EXPECT_DOUBLE_EQ(A[i], (double)i);
////		printf("Result: %d  %f\n", i, A[i]);
////	}
////
////}