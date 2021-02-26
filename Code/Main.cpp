//#include "Summation.h"
//#include "AddTwoVector.h"
#include "ShiftArray.h"
#include "pureCppFunc.h"

int main() {


    //Summation summation = Summation();
    //summation.mainFunc();

    //AddTwoVector add = AddTwoVector();
    //add.mainFunc();

    const unsigned int ARRAY_SIZE = 1000000;
    double *a = new double[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        a[i] = (double)i;
    }
    pureCppFunc shiftCpp = pureCppFunc();

    //ShiftArray shiftArray = ShiftArray();
    clock_t t1, t2;
    t1 = clock();

    //shiftArray.mainFunc();

    shiftCpp.shift(a, ARRAY_SIZE);

    t2 = clock();
    double tim = (double)(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "tim: " << tim << std::endl;



    std::cout << "======== end of main =========" <<std::endl;
    int b;
    std::cin >> b;
    return 0;
}
