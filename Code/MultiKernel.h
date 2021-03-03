#pragma once
class MultiKernel
{

protected:
    unsigned int ARRAY_SIZE;

    double* a;

public:
	MultiKernel();
    ~MultiKernel();
	void mainFunc();
};



