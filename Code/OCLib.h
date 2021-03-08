#pragma once

#include <iostream>
//#include <arrayfire.h>
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
	size_t globalSize;
	size_t localSize;
	
	cl_kernel kernels[10];
	std::vector<const char*> kernelNames;

private:
	cl_int err;
	cl_platform_id allPlatforms[5];

public:
	OCLib();
	OCLib(int ChoosenPlatformID, int ChoosenDeviceID, const char* filename, std::vector<const char*> kernelNames_);
	void DisplayPlatformsAndDevicesInfo();
	cl_platform_id choosePlatform(int ChoosenPlatformID);
	cl_device_id chooseDevice(cl_platform_id platform, int deviceID);
	cl_context createContext(cl_device_id device);
	cl_device_id create_device(cl_platform_id platform);
	void displayPlatformInfo(cl_platform_id platform);
	void displayDeviceInfo(cl_device_id device);
	void platforms_info();
	void Devices_info();
	char* readProgramSource(const char* filename);
	cl_program CreateProgram(cl_context context, char* programSource);
	void BuildProgram(cl_program& program, cl_device_id device);
	cl_mem newDoubleArrayRead(size_t Dim);
	cl_mem newIntArrayRead(size_t Dim);
	cl_mem newIntArrayReadWrit(size_t Dim);
	cl_mem newDoubleArrayWrit(size_t Dim);
	cl_mem newDoubleArrayReadWrit(size_t Dim);
	void host2Device(cl_mem& d_array, const void* h_array, size_t Dim);
	void host2DeviceInt(cl_mem& d_array, const void* h_array, size_t Dim);
	void device2Host(cl_mem& d_array, const void* h_array, size_t Dim);
	void device2Host(cl_mem& d_array, void* h_array, size_t Dim);
	void device2HostInt(cl_mem& d_array, void* h_array, size_t Dim);

	void kernelExecut(const char* kernelName, unsigned int nLoop, std::vector<unsigned int> intVar,
	                  std::vector<double> doubleVar, std::vector<cl_mem> clArray, std::vector<cl_mem> intArray);


};

