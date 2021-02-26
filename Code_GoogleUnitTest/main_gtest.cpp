bool ifBackendFailTestFail = false;

#include "gtest/gtest.h"
//#include "../../AF_LBM/AF_LBM.h"


int main(int argc, char **argv) {

	::testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();

	std::getchar();

	return true;
}
