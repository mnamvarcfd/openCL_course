#include "AddTwoVector.h"

AddTwoVector::AddTwoVector(){

    OCLpreparation = OpenCLpreparation();

    #define PROGRAM_FILE "vecAdd.cl"
    #define KERNEL_FUNC "vecAdd"
    ARRAY_SIZE = 100000;

    // Number of work items in each local work group
    localSize = 64;

    // Number of total work items - localSize must be devisor
    globalSize = ceil(ARRAY_SIZE / (float)localSize) * localSize;
    std::cout << "globalSize: " << globalSize << std::endl;;


    // Allocate memory for each vector on host
    h_a = new double[ARRAY_SIZE];
    h_b = new double[ARRAY_SIZE];
    h_c = new double[ARRAY_SIZE];

    // Initialize vectors on host
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        h_a[i] = 1.0;
        h_b[i] = 2.0;
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
    d_b = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    d_c = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, NULL);


    // Write our data set into the input array in device memory
    err  = clEnqueueWriteBuffer(queue, d_a, CL_TRUE, 0, bytes, h_a, 0, NULL, NULL);
    err |= clEnqueueWriteBuffer(queue, d_b, CL_TRUE, 0, bytes, h_b, 0, NULL, NULL);


}

void AddTwoVector::mainFunc(){



    // Set the arguments to our compute kernel
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
    err |= clSetKernelArg(kernel, 3, sizeof(unsigned int), &ARRAY_SIZE);

    // Execute the kernel over the entire range of the data set  
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);

    // Wait for the command queue to get serviced before reading back results
    clFinish(queue);

    // Read the results from the device
    clEnqueueReadBuffer(queue, d_c, CL_TRUE, 0, bytes, h_c, 0, NULL, NULL);

    //Sum up vector c and print result divided by ARRAY_SIZE, this should equal 1 within error
    double sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += h_c[i];
        //printf("h_c:  %f\n", h_c[i]);
    }
    printf("final result: %f\n", sum / ARRAY_SIZE);

    // release OpenCL resources
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    //release host memory
    free(h_a);
    free(h_b);
    free(h_c);

}