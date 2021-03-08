#include "LBMdata_OCLTest.h"

LBMdata_OCLTest::LBMdata_OCLTest()
{
    std::cout << "LBMdata_OCLTest" << std::endl;
    obj = LBMdata_OCL();

    nNode = obj.nNode;
    nVec = obj.nVec;
    nPDF = obj.nPDF;

    R = new double[nNode];
    U = new double[nNode];
    V = new double[nNode];

    sR = new double[nNode];
    sU = new double[nNode];
    sV = new double[nNode];

    fVal = new double[nPDF];

    PDFpt = new unsigned int[nPDF];


}

LBMdata_OCLTest::~LBMdata_OCLTest()
{
    std::cout << "~LBMdata_OCLTest" << std::endl;
}

void LBMdata_OCLTest::SetUp()
{
    std::cout << "SetUp" << std::endl;
    obj.init();
}

void LBMdata_OCLTest::TearDown()
{
    std::cout << "TearDown" << std::endl;
}


INSTANTIATE_TEST_CASE_P(LBM, LBMdata_OCLTest, ::testing::Values(0/*,1,2,3,4*/));

TEST_P(LBMdata_OCLTest, indirectAdressing) {

    obj.indirectAdressing();

    obj.get_fVal(fVal);
	
    for (int i = 0; i < nNode; i++) {
        EXPECT_DOUBLE_EQ(fVal[i], (double)i);
    }

}

TEST_P(LBMdata_OCLTest, macroCal) {

    obj.macroCal();

    obj.get_sR(sR);
    obj.get_sU(sU);
    obj.get_sV(sV);
	
    for (int i = 0; i < nNode; i++) {
        EXPECT_DOUBLE_EQ(sR[i], 3.6);
        EXPECT_DOUBLE_EQ(sU[i], 7.2);
        EXPECT_DOUBLE_EQ(sV[i], 1.8);
    }

}

TEST_P(LBMdata_OCLTest, collision) {

    obj.collision();

    obj.get_fVal(fVal);

    for (unsigned int k = 0; k < nVec; k++)
    {
        double result = k / 10.0 + 1.0;
        for (unsigned int j = 0; j < nNode; j++)
        {
            unsigned int i = k * nNode + j;

            EXPECT_DOUBLE_EQ(fVal[i], result);
        }
    }

}

TEST_P(LBMdata_OCLTest, macroFinal) {

    obj.macroFinal();

    obj.get_R(R);
    obj.get_U(U);
    obj.get_V(V);

    for (int i = 0; i < nNode; i++) {
        EXPECT_DOUBLE_EQ(R[i], 1.0);
        EXPECT_DOUBLE_EQ(U[i], 0.0);
        EXPECT_DOUBLE_EQ(V[i], 0.0);
    }

}

TEST_P(LBMdata_OCLTest, readWriteData) {

    obj.readWriteData();

    obj.get_sR(sR);
    obj.get_sU(sU);
    obj.get_sV(sV);
    obj.get_fVal(fVal);

    for (int i = 0; i < nNode; i++) {
        EXPECT_DOUBLE_EQ(sR[i], 9.0);
        EXPECT_DOUBLE_EQ(sU[i], 4.5);
        EXPECT_DOUBLE_EQ(sV[i], 4.5);
    }

    for (unsigned int k = 0; k < nVec; k++)
    {
        double result = k / 10.0 + 1.0;
        for (unsigned int j = 0; j < nNode; j++)
        {
            unsigned int i = k * nNode + j;

            EXPECT_DOUBLE_EQ(fVal[i], result);
        }
    }
}







