
#include "OCLib.h"

OCLib::OCLib() {

}
////////#define CL_SUCCESS_OR_RETURN(code) do { \
////////    assert(code == CL_SUCCESS); \
////////    if (code != CL_SUCCESS) { return code; } \
////////}while (0);




OCLib::OCLib(int ChoosenPlatformID, int ChoosenDeviceID, const char* filename, std::vector<const char*> kernelNames_){
	
    kernelNames = kernelNames_;
    //kernelNames.push_back("Comput") ;


    localSize = 64;

	DisplayPlatformsAndDevicesInfo();

    //Chosse a platform
    platform = choosePlatform(ChoosenPlatformID);
    printf("========== In use platform info: ===========\n");
    displayPlatformInfo(platform);

    //Chosse a device of the olatform
    device = chooseDevice(platform, ChoosenDeviceID);
    printf("========== In use device info: ===========\n");
    displayDeviceInfo(device);

    //Create a context
    context = createContext(device);

    //Read the file containing openCL code
    programSource = readProgramSource(filename);

    //Create the program
    program = CreateProgram(context, programSource);

    // Build the program executable
    BuildProgram(program, device);

    // Create the compute kernel in the program we wish to run
    for (int i = 0; i < kernelNames.size(); i++) {
        std::cout << kernelNames[i] << std::endl;
        const char* KERNEL_FUNC = kernelNames[i];
        kernels[i] = clCreateKernel(program, KERNEL_FUNC, &err);
    }
	
    //Create a command queue
    //Does not support profiling or out-of-order-execution
    queue = clCreateCommandQueue(context, device, 0, &err);
    if (err < 0) {
        perror("Couldn't create a command queue");
        exit(1);
    }



}

//From: git@github.com:sivagnanamn / opencl - device - info.git
void OCLib::DisplayPlatformsAndDevicesInfo() {

    printf("\nStarting OpenCL device query: \n");
    printf("------------------------------\n");
    cl_int err_num;
    char str_buffer[1024];
    cl_uint num_platforms_available;

    // Get the number of OpenCL capable platforms available
    err_num = clGetPlatformIDs(0, NULL, &num_platforms_available);
    //////////check_cl_error(err_num, "clGetPlatformIDs: Getting number of available platforms");

    // Exit if no OpenCL capable platform found
    if (num_platforms_available == 0) {
        printf("No OpenCL capable platforms found ! \n");
        exit(1);
    }
    else {
        printf("\n Number of OpenCL capable platforms available: %d \n", num_platforms_available);
        printf("--------------------------------------------------\n\n");
    }

    //////// Create a list for storing the platform id's
    //////cl_platform_id cl_platforms[3/*Commented by Morteza namvar: num_platforms_available*/];

    err_num = clGetPlatformIDs(num_platforms_available, allPlatforms, NULL);
    ////////////check_cl_error(err_num, "clGetPlatformIDs: Getting available platform id's");

    // Get attributes of each platform available
    for (int platform_idx = 0; platform_idx < num_platforms_available; platform_idx++) {
        printf("\t Platform ID: %d \n", platform_idx);
        printf("\t ----------------\n\n");

        // Get platform name
        err_num = clGetPlatformInfo(allPlatforms[platform_idx], CL_PLATFORM_NAME, sizeof(str_buffer), &str_buffer, NULL);
        //////////check_cl_error(err_num, "clGetPlatformInfo: Getting platform name");
        printf("\t\t [Platform %d] CL_PLATFORM_NAME: %s\n", platform_idx, str_buffer);

        // Get platform vendor
        err_num = clGetPlatformInfo(allPlatforms[platform_idx], CL_PLATFORM_VENDOR, sizeof(str_buffer), &str_buffer, NULL);
        //////////check_cl_error(err_num, "clGetPlatformInfo: Getting platform vendor");
        printf("\t\t [Platform %d] CL_PLATFORM_VENDOR: %s\n", platform_idx, str_buffer);

        // Get platform OpenCL version
        err_num = clGetPlatformInfo(allPlatforms[platform_idx], CL_PLATFORM_VERSION, sizeof(str_buffer), &str_buffer, NULL);
        //////////check_cl_error(err_num, "clGetPlatformInfo: Getting platform version");
        printf("\t\t [Platform %d] CL_PLATFORM_VERSION: %s\n", platform_idx, str_buffer);

        // Get platform OpenCL profile
        err_num = clGetPlatformInfo(allPlatforms[platform_idx], CL_PLATFORM_PROFILE, sizeof(str_buffer), &str_buffer, NULL);
        //////////check_cl_error(err_num, "clGetPlatformInfo: Getting platform profile");
        printf("\t\t [Platform %d] CL_PLATFORM_PROFILE: %s\n", platform_idx, str_buffer);

        // Get platform OpenCL supported extensions
        err_num = clGetPlatformInfo(allPlatforms[platform_idx], CL_PLATFORM_EXTENSIONS, sizeof(str_buffer), &str_buffer, NULL);
        //////////check_cl_error(err_num, "clGetPlatformInfo: Getting platform supported extensions");
        printf("\t\t [Platform %d] CL_PLATFORM_EXTENSIONS: %s\n", platform_idx, str_buffer);

        // Get the number of OpenCL supported device available in this platform
        cl_uint num_devices_available;
        err_num = clGetDeviceIDs(allPlatforms[platform_idx], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices_available);
        //////////check_cl_error(err_num, "clGetDeviceIDs: Get number of OpenCL supported devices available");
        printf("\n\t\t [Platform %d] Number of devices available: %d \n", platform_idx, num_devices_available);
        printf("\t\t ---------------------------------------------\n\n");

        cl_device_id cl_devices[5/*Commented by Morteza namvar: num_devices_available*/];
        err_num = clGetDeviceIDs(allPlatforms[platform_idx], CL_DEVICE_TYPE_ALL, num_devices_available, cl_devices, NULL);
        //////////check_cl_error(err_num, "clGetDeviceIDs: Getting available OpenCL capable device id's");

        // Get attributes of each device
        for (int device_idx = 0; device_idx < num_devices_available; device_idx++) {

            printf("\t\t\t [Platform %d] Device ID: %d\n", platform_idx, device_idx);
            printf("\t\t\t ---------------------------\n\n");

            // Get device name
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_NAME, sizeof(str_buffer), &str_buffer, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device name");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_NAME: %s\n", platform_idx, device_idx, str_buffer);

            // Get device hardware version
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_VERSION, sizeof(str_buffer), &str_buffer, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device hardware version");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_VERSION: %s\n", platform_idx, device_idx, str_buffer);

            // Get device software version
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DRIVER_VERSION, sizeof(str_buffer), &str_buffer, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device software version");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DRIVER_VERSION: %s\n", platform_idx, device_idx, str_buffer);

            // Get device OpenCL C version
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_OPENCL_C_VERSION, sizeof(str_buffer), &str_buffer, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device OpenCL C version");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_OPENCL_C_VERSION: %s\n", platform_idx, device_idx, str_buffer);

            // Get device max clock frequency
            cl_uint max_clock_freq;
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_clock_freq), &max_clock_freq, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max clock frequency");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_MAX_CLOCK_FREQUENCY: %d MHz\n", platform_idx, device_idx, max_clock_freq);

            // Get device max compute units available
            cl_uint max_compute_units_available;
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_compute_units_available), &max_compute_units_available, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max compute units available");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_MAX_COMPUTE_UNITS: %d\n", platform_idx, device_idx, max_compute_units_available);

            // Get device global mem size
            cl_ulong global_mem_size;
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(global_mem_size), &global_mem_size, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device global mem size");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_GLOBAL_MEM_SIZE: %llu MB\n", platform_idx, device_idx, (unsigned long long)global_mem_size / (1024 * 1024));

            // Get device max compute units available
            cl_ulong max_mem_alloc_size;
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(max_mem_alloc_size), &max_mem_alloc_size, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max mem alloc size");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_MAX_MEM_ALLOC_SIZE: %llu MB\n", platform_idx, device_idx, (unsigned long long)max_mem_alloc_size / (1024 * 1024));

            // Get device local mem size
            cl_ulong local_mem_size;
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(local_mem_size), &local_mem_size, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device local mem size");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_LOCAL_MEM_SIZE: %llu KB\n", platform_idx, device_idx, (unsigned long long)local_mem_size / 1024);

            // Get device max work group size
            size_t max_work_group_size;
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max work group size");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_MAX_WORK_GROUP_SIZE: %ld\n", platform_idx, device_idx, (long int)max_work_group_size);

            // Get device max work item dim
            cl_uint max_work_item_dims;
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(max_work_item_dims), &max_work_item_dims, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max work item dimension");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: %d\n", platform_idx, device_idx, max_work_item_dims);

            // Get device max work item sizes in each dimension
            size_t work_item_sizes[10 /*Commented by Morteza namvar: max_work_item_dims*/];
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(work_item_sizes), &work_item_sizes, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max work items dimension");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_MAX_WORK_ITEM_SIZES: ", platform_idx, device_idx);
            for (size_t work_item_dim = 0; work_item_dim < max_work_item_dims; work_item_dim++) {
                printf("%ld ", (long int)work_item_sizes[work_item_dim]);
            }
            printf("\n");

            // Get device image support
            cl_bool image_support;
            err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_IMAGE_SUPPORT, sizeof(image_support), &image_support, NULL);
            //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device image support");
            printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_IMAGE_SUPPORT: %u (%s)\n", platform_idx, device_idx, image_support, image_support ? "Available" : "Not available");

            if (image_support) {

                size_t image_size;

                // Get device image 2d max width
                err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(image_size), &image_size, NULL);
                //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device image max 2d width");
                printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_IMAGE2D_MAX_WIDTH: %ld\n", platform_idx, device_idx, (long int)image_size);

                // Get device image 2d max height
                err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(image_size), &image_size, NULL);
                //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device image max 2d width");
                printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_IMAGE2D_MAX_HEIGHT: %ld\n", platform_idx, device_idx, (long int)image_size);

                // Get device image 3d max width
                err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(image_size), &image_size, NULL);
                //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device image max 3d width");
                printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_IMAGE3D_MAX_WIDTH: %ld\n", platform_idx, device_idx, (long int)image_size);

                // Get device image 3d max height
                err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(image_size), &image_size, NULL);
                //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device image max 3d height");
                printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_IMAGE3D_MAX_HEIGHT: %ld\n", platform_idx, device_idx, (long int)image_size);

                // Get device image 2d max depth
                err_num = clGetDeviceInfo(cl_devices[device_idx], CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(image_size), &image_size, NULL);
                //////////check_cl_error(err_num, "clGetDeviceInfo: Getting device image max 3d depth");
                printf("\t\t\t\t\t [Platform %d] [Device %d] CL_DEVICE_IMAGE3D_MAX_DEPTH: %ld\n", platform_idx, device_idx, (long int)image_size);

            }
            printf("\n\n");
        }
    }


}

cl_platform_id OCLib::choosePlatform(int ChoosenPlatformID) {

return allPlatforms[ChoosenPlatformID];
}

/* Find a GPU or CPU associated with the first available platform

The `platform` structure identifies the first platform identified by the
OpenCL runtime. A platform identifies a vendor's installation, so a system
may have an NVIDIA platform and an AMD platform.

The `device` structure corresponds to the first accessible device
associated with the platform. Because the second parameter is
`CL_DEVICE_TYPE_GPU`, this device must be a GPU.
*/
cl_device_id OCLib::chooseDevice(cl_platform_id platform, int deviceID) {

    cl_uint deviceCount;
    cl_device_id* devices;

    // get all devices
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
    devices = (cl_device_id*)malloc(sizeof(cl_device_id) * deviceCount);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

    return devices[deviceID];
}
            
cl_context OCLib::createContext(cl_device_id device){

    cl_int err;
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (err < 0) {
        perror("Couldn't create a context");
    }

    return context;
}

/* Find a GPU or CPU associated with the first available platform

The `platform` structure identifies the first platform identified by the
OpenCL runtime. A platform identifies a vendor's installation, so a system
may have an NVIDIA platform and an AMD platform.

The `device` structure corresponds to the first accessible device
associated with the platform. Because the second parameter is
`CL_DEVICE_TYPE_GPU`, this device must be a GPU.
*/
cl_device_id OCLib::create_device(cl_platform_id platform) {

    cl_device_id dev;
    cl_int err;

    /* Identify a platform */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err < 0) {
        perror("Couldn't identify the platform");
        exit(1);
    }

    // Access a device
    // GPU
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
    if (err == CL_DEVICE_NOT_FOUND) {
        // CPU
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
    }
    if (err < 0) {
        perror("Couldn't access any devices");
        exit(1);
    }

    std::cout << dev << std::endl;
    return dev;
}


/*A platform is a specific OpenCL implementation, for instance AMD APP, NVIDIA or Intel OpenCL.
  A context is a platform with a set of available devices for that platform.And the devices are
  the actual processors(CPU, GPU etc.) that perform calculations. So if you use the Intel
  platform, a valid context with this platform would include a CPU device.While if you use the
  NVIDIA platform, a valid context would include an NVIDIA GPU device.*/
void OCLib::displayPlatformInfo(cl_platform_id platform)
{
    cl_int err;
    cl_platform_info Param_Name[5] = { CL_PLATFORM_PROFILE, CL_PLATFORM_VERSION, CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,CL_PLATFORM_EXTENSIONS };
    cl_platform_info param_name;
    size_t param_value_size;

    for (int j = 0; j < 5; j++) {
        param_name = Param_Name[j];
        err = clGetPlatformInfo(platform, param_name, 0, NULL, &param_value_size);
        char* param_value = (char*)malloc(sizeof(char) * param_value_size);
        err = clGetPlatformInfo(platform, param_name, param_value_size, param_value, NULL);

        if (j == 0) printf("PROFILE      %s\n", param_value);
        if (j == 1) printf("VERSION      %s\n", param_value);
        if (j == 2) printf("NAME         %s\n", param_value);
        if (j == 3) printf("VENDOR       %s\n", param_value);
        //if (j == 4) printf("EXTENSIONS   %s\n", param_value);
        free(param_value);
    }

}

void OCLib::displayDeviceInfo(cl_device_id device)
{

cl_int err_num;
char str_buffer[1024];

// Get device name
err_num = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(str_buffer), &str_buffer, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device name");
printf("CL_DEVICE_NAME:                    %s\n",  str_buffer);

// Get device hardware version
err_num = clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(str_buffer), &str_buffer, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device hardware version");
printf("CL_DEVICE_VERSION:                 %s\n", str_buffer);

// Get device software version
err_num = clGetDeviceInfo(device, CL_DRIVER_VERSION, sizeof(str_buffer), &str_buffer, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device software version");
printf("CL_DRIVER_VERSION:                 %s\n", str_buffer);

// Get device OpenCL C version
err_num = clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, sizeof(str_buffer), &str_buffer, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device OpenCL C version");
printf("CL_DEVICE_OPENCL_C_VERSION:        %s\n", str_buffer);

// Get device max clock frequency
cl_uint max_clock_freq;
err_num = clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_clock_freq), &max_clock_freq, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max clock frequency");
printf("CL_DEVICE_MAX_CLOCK_FREQUENCY:     %d MHz\n", max_clock_freq);

// Get device max compute units available
cl_uint max_compute_units_available;
err_num = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_compute_units_available), &max_compute_units_available, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max compute units available");
printf("CL_DEVICE_MAX_COMPUTE_UNITS:       %d\n", max_compute_units_available);

// Get device global mem size
cl_ulong global_mem_size;
err_num = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(global_mem_size), &global_mem_size, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device global mem size");
printf("CL_DEVICE_GLOBAL_MEM_SIZE:         %llu MB\n", (unsigned long long)global_mem_size / (1024 * 1024));

// Get device max compute units available
cl_ulong max_mem_alloc_size;
err_num = clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(max_mem_alloc_size), &max_mem_alloc_size, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max mem alloc size");
printf("CL_DEVICE_MAX_MEM_ALLOC_SIZE:      %llu MB\n", (unsigned long long)max_mem_alloc_size / (1024 * 1024));

// Get device local mem size
cl_ulong local_mem_size;
err_num = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(local_mem_size), &local_mem_size, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device local mem size");
printf("CL_DEVICE_LOCAL_MEM_SIZE:          %llu KB\n", (unsigned long long)local_mem_size / 1024);

// Get device max work group size
size_t max_work_group_size;
err_num = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max work group size");
printf("CL_DEVICE_MAX_WORK_GROUP_SIZE:     %ld\n", (long int)max_work_group_size);

// Get device max work item dim
cl_uint max_work_item_dims;
err_num = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(max_work_item_dims), &max_work_item_dims, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max work item dimension");
printf("CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:%d\n", max_work_item_dims);

// Get device max work item sizes in each dimension
size_t work_item_sizes[10 /*Commented by Morteza namvar: max_work_item_dims*/];
err_num = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(work_item_sizes), &work_item_sizes, NULL);
//////////check_cl_error(err_num, "clGetDeviceInfo: Getting device max work items dimension");
printf("CL_DEVICE_MAX_WORK_ITEM_SIZES:     " );
for (size_t work_item_dim = 0; work_item_dim < max_work_item_dims; work_item_dim++) {
    printf("%ld ", (long int)work_item_sizes[work_item_dim]);
}
printf("\n");


}


void OCLib::platforms_info()
{
  /*A platform is a specific OpenCL implementation, for instance AMD APP, NVIDIA or Intel OpenCL.
    A context is a platform with a set of available devices for that platform.And the devices are 
    the actual processors(CPU, GPU etc.) that perform calculations. So if you use the Intel 
    platform, a valid context with this platform would include a CPU device.While if you use the 
    NVIDIA platform, a valid context would include an NVIDIA GPU device.*/
    printf("=============================== Platforms info ==============================\n");
    cl_int err;
    cl_uint numPlatforms;
    cl_platform_id* platforms;

    err = clGetPlatformIDs(0, NULL, &numPlatforms);
    if (err != CL_SUCCESS || numPlatforms == 0) {
        printf("Couldn't identify a platform");
        //return EXIT_FAILURE;
    }
    printf("Number of platfroms: %d\n", numPlatforms);

    platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * numPlatforms);
    err = clGetPlatformIDs(numPlatforms, platforms, NULL);
    if (err != CL_SUCCESS) {
        printf("Couldn't get platforms");
        //return EXIT_FAILURE;
    }

    cl_platform_info Param_Name[5] = { CL_PLATFORM_PROFILE, CL_PLATFORM_VERSION, CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,CL_PLATFORM_EXTENSIONS };
    cl_platform_info param_name;
    size_t param_value_size;
    for (int i = 0; i < (int)numPlatforms; i++) {
        printf("---------------------- Platform %d info:\n", i);
        for (int j = 0; j < 5-1; j++) {
            param_name = Param_Name[j];
            err = clGetPlatformInfo(platforms[i], param_name, 0, NULL, &param_value_size);
            char* param_value = (char*)malloc(sizeof(char) * param_value_size);
            err = clGetPlatformInfo(platforms[i], param_name, param_value_size, param_value, NULL);

            if (j == 0) printf("PROFILE  %s\n", param_value);
            if (j == 1) printf("VERSION  %s\n", param_value);
            if (j == 2) printf("NAME     %s\n", param_value);
            if (j == 3) printf("VENDOR   %s\n", param_value);
            free(param_value);
        }
    }
    free(platforms);
    printf("==============================End of Platforms info ==========================\n");
            
}


void OCLib::Devices_info() {
    printf("================================ Devices info ================================\n");

    char* value;
    size_t valueSize;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
    cl_uint maxComputeUnits;

    // get all platforms
    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);

    for (int i = 0; i < (int)platformCount; i++) {

        // get all devices
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = (cl_device_id*)malloc(sizeof(cl_device_id) * deviceCount);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        printf("Nember of devices of platform %d is %d and its devices info is:\n", i, (int)deviceCount);
        // for each device print critical attributes
        for (int j = 0; j < (int)deviceCount; j++) {
           
            // print device name
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = (char*)malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            printf("%d. Device: %s\n", j + 1, value);
            free(value);

            // print hardware device version
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = (char*)malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            printf(" %d.%d Hardware version: %s\n", j + 1, 1, value);
            free(value);

            // print software driver version
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
            value = (char*)malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
            printf(" %d.%d Software version: %s\n", j + 1, 2, value);
            free(value);

            // print c version supported by compiler for device
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
            value = (char*)malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
            printf(" %d.%d OpenCL C version: %s\n", j + 1, 3, value);
            free(value);

            // print parallel compute units
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf(" %d.%d Parallel compute units: %d\n", j + 1, 4, maxComputeUnits);

        }

        free(devices);

    }

    free(platforms);
    printf("============================ End of Devices info =============================\n");



}

void check_cl_error(cl_int err_num, char* msg) {
    if (err_num != CL_SUCCESS) {
        printf("[Error] OpenCL error code: %d in %s \n", err_num, msg);
        exit(EXIT_FAILURE);
    }
}

/* Create program from a file and compile it */
char* OCLib::readProgramSource(const char* filename) {

    FILE* file;

    /* Read program file and place content into buffer */
    fopen_s(&file, filename, "rb");
    if (file == NULL) {
        perror("Couldn't find the program file");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size_t programSourceSize = ftell(file);
    rewind(file);
    programSource = (char*)malloc(programSourceSize + 1);
    programSource[programSourceSize] = '\0';
    fread(programSource, sizeof(char), programSourceSize, file);
    fclose(file);

    std::cout << "openCL code in the file <" << filename << "> has been read." << std::endl;

    return programSource;
}


cl_program OCLib::CreateProgram(cl_context context, char* programSource){

    cl_program program;
    int err;

    /* Create program from file

    Creates a program from the source code in the add_numbers.cl file.
    Specifically, the code reads the file's content into a char array
    called program_buffer, and then calls clCreateProgramWithSource.
    */


    size_t programSourceSize = strlen(programSource);

    program = clCreateProgramWithSource(context, 1,
        (const char**)&programSource, &programSourceSize, &err);
    if (err < 0) {
        perror("Couldn't create the program");
        exit(1);
    }
    free(programSource);

    return program;
}


 void OCLib::BuildProgram(cl_program &program, cl_device_id device) {
/* Build program

The fourth parameter accepts options that configure the compilation.
These are similar to the flags used by gcc. For example, you can
define a macro with the option -DMACRO=VALUE and turn off optimization
with -cl-opt-disable.
*/


    char* program_log;
    size_t log_size;
    int err;

    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err < 0) {

        /* Find size of log and print to std output */
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
            0, NULL, &log_size);
        program_log = (char*)malloc(log_size + 1);
        program_log[log_size] = '\0';
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
            log_size + 1, program_log, NULL);
        printf("%s\n", program_log);
        free(program_log);
        exit(1);
    }

}
 

 cl_mem OCLib::newDoubleArrayRead(size_t Dim) {
     size_t bytes = Dim * sizeof(double);
     cl_mem Array = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
     return Array;
 }

 cl_mem OCLib::newDoubleArrayWrit(size_t Dim) {
     size_t bytes = Dim * sizeof(double);
     cl_mem Array = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
     return Array;
 }

 cl_mem OCLib::newDoubleArrayReadWrit(size_t Dim) {
     size_t bytes = Dim * sizeof(double);
     cl_mem Array = clCreateBuffer(context, CL_MEM_READ_WRITE, bytes, NULL, NULL);
     return Array;
 }


 void OCLib::host2Device(cl_mem& d_array, const void* h_array, size_t Dim) {

     size_t bytes = Dim * sizeof(h_array);
     clEnqueueWriteBuffer(queue, d_array, CL_TRUE, 0, bytes, h_array, 0, NULL, NULL);
 }

 void OCLib::device2Host(cl_mem& d_array, void* h_array, size_t Dim) {

     size_t bytes = Dim * sizeof(h_array);
     clEnqueueReadBuffer(queue, d_array, CL_TRUE, 0, bytes, h_array, 0, NULL, NULL);
 }




 void OCLib::kernelExecut(const char* kernelName, std::vector<size_t> intVar, std::vector<cl_mem> clArray)
 {
     cl_kernel kernel = kernels[0];
  
     globalSize = intVar[0];

	for(int i=0; i<5; i++)
	{
        if (kernelNames[i] == kernelName) {
            kernel = kernels[i];
        }
	}

     // Set the arguments to our compute kernel
     for (int i = 0; i < clArray.size(); i++) {
         //std::cout << "clArray  "<< i << std::endl;
         err = clSetKernelArg(kernel, i, sizeof(cl_mem), &clArray[i]);
     }
     for (int i = 1; i < intVar.size(); i++) {
         //std::cout << "intVar  " << i << std::endl;
         err = clSetKernelArg(kernel, i + clArray.size()-1, sizeof(unsigned int), &intVar[i]);
     }

     //err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
     //err |= clSetKernelArg(kernel, 1, sizeof(unsigned int), &ARRAY_SIZE);


     // Execute the kernel over the entire range of the data set  
     err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);


     //std::cout << "error  : "<< err << std::endl;
     // Wait for the command queue to get serviced before reading back results
     clFinish(queue);

 }