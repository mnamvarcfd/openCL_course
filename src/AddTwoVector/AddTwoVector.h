#pragma once
class AddTwoVector
{

public:
    unsigned int arraySize;

    double* a;
    double* b;
    double* c;

public:
	AddTwoVector();
    ~AddTwoVector();
	void mainFunc();
    void get_c(double* Arr);
};



