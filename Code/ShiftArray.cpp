#include "ShiftArray.h"

ShiftArray::ShiftArray(){

    OCLpreparation = OpenCLpreparation();

    #define PROGRAM_FILE "Shift.cl"
    #define KERNEL_FUNC "Shift"
    ARRAY_SIZE = 1000000000;
    lengt = 2;

    // Number of work items in each local work group
    localSize = 64;

    // Number of total work items - localSize must be devisor
    globalSize = ceil(ARRAY_SIZE / (float)localSize) * localSize / lengt;
    std::cout << "globalSize: " << globalSize << std::endl;;


    // Allocate memory for each vector on host
    h_a = new double[ARRAY_SIZE];

    // Initialize vectors on host
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        h_a[i] = (double)i;
    }


    //Create device
    device = OCLpreparation.create_device();

    //Create context
    //Creates a context containing only one device — the device structure
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (err < 0) {
        perror("Couldn't create a context");
        exit(1);
    }

    /* Build program */
    program = OCLpreparation.build_program(context, device, PROGRAM_FILE);

    //Create a command queue
    //Does not support profiling or out-of-order-execution
    queue = clCreateCommandQueue(context, device, 0, &err);
    if (err < 0) {
        perror("Couldn't create a command queue");
        exit(1);
    };


    // Build the program executable 
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    // Create the compute kernel in the program we wish to run
    kernel = clCreateKernel(program, KERNEL_FUNC, &err);

    // Create the input and output arrays in device memory for our calculation
    // Size, in bytes, of each vector
    bytes = ARRAY_SIZE * sizeof(double);
    d_a = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);


    // Write our data set into the input array in device memory
    err  = clEnqueueWriteBuffer(queue, d_a, CL_TRUE, 0, bytes, h_a, 0, NULL, NULL);


}

void ShiftArray::mainFunc(){



    // Set the arguments to our compute kernel
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    err |= clSetKernelArg(kernel, 1, sizeof(unsigned int), &ARRAY_SIZE);
    err |= clSetKernelArg(kernel, 2, sizeof(int), &lengt);

    // Execute the kernel over the entire range of the data set  
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);

    // Wait for the command queue to get serviced before reading back results
    clFinish(queue);

    // Read the results from the device
    clEnqueueReadBuffer(queue, d_a, CL_TRUE, 0, bytes, h_a, 0, NULL, NULL);

    //Sum up vector c and print result divided by ARRAY_SIZE, this should equal 1 within error
    for (int i = 0; i < ARRAY_SIZE; i++) {
        //printf("h_a: %d  %f\n", i , h_a[i]);
    }
    for (int i = 1; i < ARRAY_SIZE; i++) {
        //printf("h_a: %d  %f\n", i, ( (double)i- h_a[i] ));
    }

    for (int i = 1; i < ARRAY_SIZE; i++) {
        if ( ((i+1)%lengt)==0 ) {
            if (((double)i - h_a[i]) > 1.0) printf("failed at %d \n", i);
        }
        else {
            //printf("============ %d \n", i);
        }
    }
    
    // release OpenCL resources
    clReleaseMemObject(d_a);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    //release host memory
    free(h_a);

}