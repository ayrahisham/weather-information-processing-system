#define CL_USE_DEPRECATED_OPENCL_2_0_APIS	// using OpenCL 1.2, some functions deprecated in OpenCL 2.
#define __CL_ENABLE_EXCEPTIONS				// enable OpenCL exemption


// C++ standard library and STL header
#include <iostream
#include <vector


// OpenCL header, depending on O
#ifdef __APPLE_
#include <OpenCL/cl.hpp
#els
#include <CL/cl.hpp
#endi


// functions to handle error
#include "error.h


// to avoid having to use prefixe
//using namespace std
//using namespace cl


int main(void)

	std::vector<cl::Platform> platforms;	// available platform
	std::vector<cl::Device> devices;		// devices available to a platfor
	std::string outputString;				// string for outpu
	unsigned int i, j;						// counter


	// Based on the user’s choice, display the following information for each CPU/GPU device
	// that is available on the system 
	try
	
		// get the number of available OpenCL platform
		cl::Platform::get(&platforms)
		std::cout << "Number of OpenCL platforms: " << platforms.size() << std::endl


		// for each platfor
		for (i = 0; i < platforms.size(); i++)
		
			std::cout << "--------------------" << std::endl
			// output platform inde
			std::cout << "  Platform " << i << ":" << std::endl


			// get and output platform nam
			platforms[i].getInfo(CL_PLATFORM_NAME, &outputString)
			std::cout << "\tName: " << outputString << std::endl


			// get and output platform vendor nam
			outputString = platforms[i].getInfo<CL_PLATFORM_VENDOR>()
			std::cout << "\tVendor: " << outputString << std::endl


			// get and output OpenCL version supported by the platfor
			outputString = platforms[i].getInfo<CL_PLATFORM_VERSION>()
			std::cout << "\tVersion: " << outputString << std::endl


			// get all devices available to the platfor
			platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &devices)


			std::cout << "\nNumber of devices available to platform " << i << ": " << devices.size() << std::endl
			std::cout << "--------------------" << std::endl


			// for each devic
			for (j = 0; j < devices.size(); j++)
			
				// output device inde
				std::cout << "  Device " << j << std::endl


				// get and output device nam
				outputString = devices[j].getInfo<CL_DEVICE_NAME>()
				std::cout << "\tName: " << outputString << std::endl


				// get and output device typ
				cl_device_type type
				devices[j].getInfo(CL_DEVICE_TYPE, &type)
				if (type == CL_DEVICE_TYPE_CPU
					std::cout << "\tType: " << "CPU" << std::endl
				else if (type == CL_DEVICE_TYPE_GPU
					std::cout << "\tType: " << "GPU" << std::endl
				els
					std::cout << "\tType: " << "Other" << std::endl


				// get and output device vendo
				outputString = devices[j].getInfo<CL_DEVICE_VENDOR>()
				std::cout << "\tVendor: " << outputString << std::endl


				// get and output OpenCL version supported by the devic
				outputString = devices[j].getInfo<CL_DEVICE_VERSION>()
				std::cout << "\tVersion: " << outputString << std::endl
			
			std::cout << "--------------------" << std::endl
		
	
	// catch any OpenCL function error
	catch (cl::Error e) 
		// call function to handle error
		handle_error(e)
	


#ifdef _WIN3
	// wait for a keypress on Windows OS before exitin
	std::cout << "\npress a key to quit..."
	std::cin.ignore()
#endi


	return 0
}

