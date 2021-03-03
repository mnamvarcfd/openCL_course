#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <iostream>

#include <arrayfire.h>
#include <CL/cl.h>
#include <CL/cl.hpp>

class OCLib
{



public:
	cl_platform_id platform;
	cl_device_id device;       
	cl_context context;              
	cl_command_queue queue;           
	cl_program program;                  
	char* programSource;
	size_t globalSize, localSize;

	
	cl_kernel kernels[5];
	std::vector<const char*> kernelNames;

private:
	cl_int err;
	cl_platform_id allPlatforms[5];
	cl_platform_id inUsePlatform;
	cl_device_id inUseDevice;

public:
	OCLib();
	OCLib(int ChoosenPlatformID, int ChoosenDeviceID, const char* filename,
	                  std::vector<const char*> kernelNames_);
	OCLib(int ChoosenPlatformID, int ChoosenDeviceID, const char* filename,
	                  std::vector<std::string> kernelNames);
	void DisplayPlatformsAndDeviceInfo();
	OCLib(int ChoosenPlatformID, int ChoosenDeviceID, const char* filename);
	void DisplayPlatformsAndDevicesInfo();
	cl_platform_id choosePlatform(int ChoosenPlatformID);
	cl_platform_id create_platform(int ChoosenPlatformID);
	cl_device_id create_device(cl_platform_id platform, int deviceID);
	cl_device_id chooseDevice(cl_platform_id platform, int deviceID);
	cl_context createContext(cl_device_id device);
	cl_context create_context(cl_device_id device);
	void DisplayPlatformsAndDeviceInfo(cl_platform_id cl_platforms);
	void DisplayPlatformsAndDeviceInfo(cl_platform_id& cl_platforms);
	cl_device_id create_device();
	cl_device_id create_device(cl_platform_id platform);
	void displayPlatformInfo(cl_platform_id platform);
	void displayDeviceInfo(cl_device_id device);
	void platforms_info();
	void Devices_info();
	void info();
	void platformsAndDevice_info();
	cl_context creatContext(cl_context device);
	cl_context creatContext(cl_context &device);
	char* readProgramSource(const char* filename);
	cl_program CreateProgram(cl_context context, char* programSource);
	void BuildProgram(cl_program& program, cl_device_id device);

	cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename);
	cl_mem newDoubleArrayRead(size_t Dim);
	cl_mem newDoubleArrayWrit(size_t Dim);
	cl_mem newDoubleArrayReadWrit(size_t Dim);


	void host2Device(cl_mem& d_a, const void* h_a, size_t Dim);
	void device2Host(cl_mem& d_array, void* h_array, size_t Dim);
	void kernelExecut(const char* kernelName, std::vector<size_t> intVar, std::vector<cl_mem> clArray);
};

