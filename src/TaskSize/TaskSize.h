#pragma once
class TaskSize
{

public:
    unsigned int arraySize;

    double* a;

public:
	TaskSize();
    ~TaskSize();
	void mainFunc();
    void get_a(double* Arr);
};



