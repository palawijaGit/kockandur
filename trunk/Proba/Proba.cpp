/*
 * Copyright 1993-2010 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */

/* This sample queries and logs the properties of the CUDA devices present in the system. */

// Standard utilities and common systems includes
#include <oclUtils.h>

#include <sstream>
#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char** argv) 
{
    std::cout << "This is a test" << std::endl;

    cl_int errorNum = CL_SUCCESS; 
    cl_uint deviceCount = 0;
    cl_platform_id  platformId = NULL;
    cl_device_id * devices = NULL;

    errorNum = oclGetPlatformID(&platformId);
    if (errorNum != CL_SUCCESS) { 
        std::cout << "Getting platform IDs were unsuccesfull" << std::endl;
        return -1; 
    } 

    errorNum = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 0, NULL, &deviceCount);
    devices = (cl_device_id *) malloc (deviceCount * sizeof(cl_device_id)); 
    errorNum = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, deviceCount, devices, NULL);
    if (errorNum != CL_SUCCESS) { 
        std::cout << "Getting device IDs were unsuccessfull" << std::endl; 
    } else { 
        std::cout << "Getting device IDs were successfull" << std::endl; 
    } 

    cl_context cxGPUContext;
    
    cxGPUContext = clCreateContext(0, deviceCount, devices, NULL, NULL, &errorNum);
    if (errorNum != CL_SUCCESS) { 
        std::cout << "Creating device context were unsuccessfull" << std::endl;
    } else { 
        std::cout << "Creating device context were successfull" << std::endl;
    } 

    // Program Setup
    size_t program_length;
    const char* header_path = shrFindFilePath("filter.h", argv[0]);
    std::cout << header_path << std::endl;
    oclCheckError(header_path != NULL, shrTRUE);
    char* header = oclLoadProgSource(header_path, "", &program_length);
    if(!header)
    {
        shrLog("Error: Failed to load the header %s!\n", header_path);
        return -1000;
    }
    const char* source_path = shrFindFilePath("filter.cl", argv[0]);
    oclCheckError(source_path != NULL, shrTRUE);
    char *source = oclLoadProgSource(source_path, header, &program_length);
    if(!source)
    {
        shrLog("Error: Failed to load compute program %s!\n", source_path);
        return -2000;
    }

    // create the program
    cl_program cpProgram = clCreateProgramWithSource(cxGPUContext, 1, (const char **)&source, 
                                                    &program_length, &errorNum);
    if (errorNum != CL_SUCCESS)
    {
        shrLog("Error: Failed to create program\n");
        return errorNum;
    }
    free(header);
    free(source);

    return 0;
}

void SobelOperator() { 
    
} 
