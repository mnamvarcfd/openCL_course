#include "LBMdataTest.h"



LBMdataTest::LBMdataTest()
{
	std::cout << "LBMdataTest" << std::endl;
	objCpp = LBMdata();

    nNode = objCpp.nNode;
    nVec = objCpp.nVec;
    nPDF = objCpp.nPDF;

    R = new double[nNode];
    U = new double[nNode];
    V = new double[nNode];

    sR = new double[nNode];
    sU = new double[nNode];
    sV = new double[nNode];

    fVal = new double[nPDF];

    PDFpt = new unsigned int[nPDF];


}

LBMdataTest::~LBMdataTest()
{
	std::cout << "~LBMdataTest" << std::endl;
}

void LBMdataTest::SetUp()
{
	std::cout << "SetUp" << std::endl;
	objCpp.init();
}

void LBMdataTest::TearDown()
{
	std::cout << "TearDown" << std::endl;
}


INSTANTIATE_TEST_CASE_P(LBM, LBMdataTest, ::testing::Values(0/*,1,2,3,4*/));


TEST_P(LBMdataTest, indirectAdressing) {

    objCpp.indirectAdressing();

    objCpp.get_fVal(fVal);

    for (int i = 0; i < nNode; i++) {
        EXPECT_DOUBLE_EQ(fVal[i], (double)i);
    }

}

TEST_P(LBMdataTest, macroCal) {

	objCpp.macroCal();

	objCpp.get_sR(sR);
	objCpp.get_sU(sU);
	objCpp.get_sV(sV);

	for (int i = 0; i < nNode; i++) {
		EXPECT_DOUBLE_EQ(sR[i] , 3.6);
        EXPECT_DOUBLE_EQ(sU[i] , 7.2);
        EXPECT_DOUBLE_EQ(sV[i] , 1.8);
	}

}

TEST_P(LBMdataTest, collision) {

	objCpp.collision();

	objCpp.get_fVal(fVal);

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

TEST_P(LBMdataTest, macroFinal) {

    objCpp.macroFinal();

    objCpp.get_R(R);
    objCpp.get_U(U);
    objCpp.get_V(V);

    for (int i = 0; i < nNode; i++) {
        EXPECT_DOUBLE_EQ(R[i], 1.0);
        EXPECT_DOUBLE_EQ(U[i], 0.0);
        EXPECT_DOUBLE_EQ(V[i], 0.0);
    }

}

TEST_P(LBMdataTest, readWriteData) {

    objCpp.readWriteData();

    objCpp.get_sR(sR);
    objCpp.get_sU(sU);
    objCpp.get_sV(sV);
    objCpp.get_fVal(fVal);

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






