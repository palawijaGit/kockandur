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
#include <GL/glut.h>

#include <sstream>
#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////

const unsigned int PGMHeaderSize = 0x40;

int BlockDimX = 16;
int BlockDimY = 16;

unsigned int  width;
unsigned int  height; 

int iProcFlag = 0;                  // 0 = GPU, 1 = CPU
bool bFullScreen = false;           // state var for full screen mode or not
bool bFilter = true;                // state var for whether filter is enaged or not
float fZoom = 1.0f;                 // pixel display zoom   
int iGraphicsWinPosX = 0;           // GL Window X location
int iGraphicsWinPosY = 0;           // GL Window Y location
int iGraphicsWinWidth = 1024;       // GL Window width
int iGraphicsWinHeight = iGraphicsWinWidth;  // GL Windows height
int iGLUTWindowHandle;              // handle to the GLUT window
cl_uint* uiInput = NULL;            // Mapped Pointer to pinned Host input buffer for host processing
cl_uchar* uiOutput = NULL;           // Mapped Pointer to pinned Host output buffer for host processing
cl_uchar* uiInput2 = NULL;            // Mapped Pointer to pinned Host input buffer for host processing
cl_uchar* uiOutput2 = NULL;           // Mapped Pointer to pinned Host output buffer for host processin
cl_uchar* uiInput3 = NULL;            // Mapped Pointer to pinned Host input buffer for host processing
cl_uchar* uiOutput3 = NULL;           // Mapped Pointer to pinned Host output buffer for host processin

unsigned char * image;
unsigned int  channels;
unsigned threshold = 100;

cl_int errorNum = CL_SUCCESS; 
cl_uint deviceCount = 0;
cl_platform_id  platformId = NULL;
cl_device_id * devices = NULL;
cl_context cxGPUContext;
cl_program cpProgram;
cl_kernel ckProba;
cl_command_queue commandqueue;
size_t szLocalWorkSize[2];
size_t szGlobalWorkSize[2];
size_t szBuffBytes;
size_t szBuffBytesout;

cl_mem cmPinnedBufIn;               // OpenCL host memory input buffer object:  pinned 
cl_mem cmPinnedBufOut;
cl_mem cmPinnedBufIn2;               // OpenCL host memory input buffer object:  pinned 
cl_mem cmPinnedBufOut2;
cl_mem cmPinnedBufIn3;               // OpenCL host memory input buffer object:  pinned 
cl_mem cmPinnedBufOut3;


cl_mem cmDevBufIn; 
cl_mem cmDevBufOut;

void InitGL(int* argc, char** argv);
void DeInitGL();
void DisplayGL();
void Reshape(int w, int h);
void Idle(void);
void KeyboardGL(unsigned char key, int x, int y);
void LoadPPM4ub( const char* file, unsigned char** OutData, unsigned int *w, unsigned int *h);
bool loadPPMHeader(const char * file, unsigned int * w, unsigned *h, unsigned int * channels) { 
    FILE* fp = 0;

    if ((fp = fopen(file, "rb")) == 0)
        {
            // if error on attempt to open, be sure the file is null or close it, then return negative error code
            if (fp)
                {
                    fclose (fp);
                }
            std::cerr << "loadPPM() : Failed to open file: " << file << std::endl;
            return false;
        }
    
    // check header
    char header[PGMHeaderSize];
    if ((fgets( header, PGMHeaderSize, fp) == NULL) && ferror(fp)) {
        if (fp)
            {
                fclose (fp);
            }
        std::cerr << "loadPPM() : File is not a valid PPM or PGM image" << std::endl;
        *channels = 0;
        return false;
    }
    
    if (strncmp(header, "P5", 2) == 0)
    {
        *channels = 1;
    }
    else if (strncmp(header, "P6", 2) == 0)
    {
        *channels = 3;
    }
    else
    {
        std::cerr << "loadPPM() : File is not a PPM or PGM image" << std::endl;
        *channels = 0;
        return shrFALSE;
    }

    // parse header, read maxval, width and height
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int maxval = 0;
    unsigned int i = 0;
    while(i < 3) 
    {
        if ((fgets(header, PGMHeaderSize, fp) == NULL) && ferror(fp))
        {
            if (fp)
            {
                fclose (fp);
            }
            std::cerr << "loadPPM() : File is not a valid PPM or PGM image" << std::endl;
            return shrFALSE;
        }
        if(header[0] == '#') continue;

        if(i == 0) {
            i += sscanf(header, "%u %u %u", &width, &height, &maxval);
        } else if (i == 1) {
            i += sscanf(header, "%u %u", &height, &maxval);
        } else if (i == 2) {
            i += sscanf(header, "%u", &maxval);
        }
    }
    *w = width;
    *h = height;
    if (fp) {
        fclose (fp);
    }
    
    return true;
} 

bool loadPPM_(const char* file, unsigned char** data, 
            unsigned int *w, unsigned int *h, unsigned int *channels) 
{
    FILE* fp = 0;

    if ((fp = fopen(file, "rb")) == 0)
        {
            // if error on attempt to open, be sure the file is null or close it, then return negative error code
            if (fp)
                {
                    fclose (fp);
                }
            std::cerr << "loadPPM() : Failed to open file: " << file << std::endl;
            return false;
        }
    
    // check header
    char header[PGMHeaderSize];
    if ((fgets( header, PGMHeaderSize, fp) == NULL) && ferror(fp)) {
        if (fp)
            {
                fclose (fp);
            }
        std::cerr << "loadPPM() : File is not a valid PPM or PGM image" << std::endl;
        *channels = 0;
        return false;
    }
    
    if (strncmp(header, "P5", 2) == 0)
    {
        *channels = 1;
    }
    else if (strncmp(header, "P6", 2) == 0)
    {
        *channels = 3;
    }
    else
    {
        std::cerr << "loadPPM() : File is not a PPM or PGM image" << std::endl;
        *channels = 0;
        return shrFALSE;
    }

    // parse header, read maxval, width and height
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int maxval = 0;
    unsigned int i = 0;
    while(i < 3) 
    {
        if ((fgets(header, PGMHeaderSize, fp) == NULL) && ferror(fp))
        {
            if (fp)
            {
                fclose (fp);
            }
            std::cerr << "loadPPM() : File is not a valid PPM or PGM image" << std::endl;
            return shrFALSE;
        }
        if(header[0] == '#') continue;

        if(i == 0) {
            i += sscanf(header, "%u %u %u", &width, &height, &maxval);
        } else if (i == 1) {
            i += sscanf(header, "%u %u", &height, &maxval);
        } else if (i == 2) {
            i += sscanf(header, "%u", &maxval);
        }
    }

    // check if given handle for the data is initialized
    if(NULL != *data) 
    {
        if (*w != width || *h != height) 
        {
            fclose(fp);
            std::cerr << "loadPPM() : Invalid image dimensions." << std::endl;
            return false;
        }
    } 
    else 
    {
        *data = (unsigned char*)malloc( sizeof(unsigned char) * width * height * *channels);
        *w = width;
        *h = height;
    }

    // read and close file
    if (fread(*data, sizeof(unsigned char), width * height * *channels, fp) != width * height * *channels)
    {
        fclose(fp);
        std::cerr << "loadPPM() : Invalid image." << std::endl;
        return false;
    }
    fclose(fp);

    return true;
}

void LoadPPM4ub( const char* file, unsigned char** OutData, unsigned int *w, unsigned int *h) {
    unsigned char* cLocalData = 0;
    unsigned int channels;                                                                           
    loadPPM_(file, &cLocalData, w, h, &channels);

    int size = *w * *h;                                                                                                                                                                                    
    if (*OutData == NULL)           
        *OutData = (unsigned char*)malloc(sizeof(unsigned char) * size * 4);                              unsigned char* cTemp = cLocalData;                                                                    unsigned char* cOutPtr = *OutData;                                                                                                                                              
    // transfer data, padding 4th element                                                                                                                                                                  
    for(int i=0; i<size; i++){                                                                        
            *cOutPtr++ = *cTemp++;                                                                    
            *cOutPtr++ = *cTemp++;                                                                    
            *cOutPtr++ = *cTemp++;                                                    
            *cOutPtr++ = 0;
        }                                                                                             
    // free temp lcoal buffer and return OK                                                                                                    
    free(cLocalData);
}

void CleanUp(int) { 
    return;
} 

void Rgb2GrayScale(cl_uint* uiInputImage = NULL, cl_uchar* uiOutputImage = NULL) { 

    ckProba = clCreateKernel(cpProgram, "Rgb2GrayScale", &errorNum);
    if (errorNum != CL_SUCCESS)
    {
        shrLog("Error: Failed to create kernel\n");
        exit(0);
    }

    cmDevBufIn = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY, szBuffBytes, NULL, &errorNum);
    cmDevBufOut = clCreateBuffer(cxGPUContext, CL_MEM_WRITE_ONLY, szBuffBytesout, NULL, &errorNum);
        
    szLocalWorkSize[0] = BlockDimX;
    szLocalWorkSize[1] = BlockDimY;
    szGlobalWorkSize[0] = shrRoundUp((int)szLocalWorkSize[0], width); 
    szGlobalWorkSize[1] = shrRoundUp((int)szLocalWorkSize[1], height);

    errorNum = clSetKernelArg(ckProba, 0, sizeof(cl_mem), (void*) &cmDevBufIn);
    errorNum |= clSetKernelArg(ckProba, 1, sizeof(cl_mem), (void*) &cmDevBufOut);
    errorNum |= clSetKernelArg(ckProba, 2, sizeof(cl_uint), (void*) &width);
    errorNum |= clSetKernelArg(ckProba, 3, sizeof(cl_uint), (void*) &height);

    std::cout << "Running processing\n";
    errorNum = 0; 
    errorNum |= clEnqueueWriteBuffer(commandqueue, cmDevBufIn, CL_FALSE, 0, szBuffBytes, 
                                       (void*)&uiInputImage[0], 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    errorNum |= clEnqueueNDRangeKernel(commandqueue, ckProba, 2, NULL, szGlobalWorkSize, szLocalWorkSize, 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    errorNum |= clEnqueueReadBuffer(commandqueue, cmDevBufOut, CL_FALSE, 0, szBuffBytesout, (void*)&uiOutputImage[0], 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    if (!errorNum) { 
        std::cout << "clFinish ended succesfully\n";
    } else { 
        std::cout << "clFinish failed\n";
    }

    return;
}

void BwFill(cl_uchar * uiInputImage = NULL, cl_uchar * uiOutputImage = NULL) { 
    ckProba = clCreateKernel(cpProgram, "MorphFit", &errorNum);
    if (errorNum != CL_SUCCESS)
    {
        shrLog("Error: Failed to create kernel\n");
        exit(0);
    }

    cmDevBufIn = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY, szBuffBytesout, NULL, &errorNum);
    cmDevBufOut = clCreateBuffer(cxGPUContext, CL_MEM_WRITE_ONLY, szBuffBytesout, NULL, &errorNum);
        
    szLocalWorkSize[0] = BlockDimX;
    szLocalWorkSize[1] = BlockDimY;
    szGlobalWorkSize[0] = shrRoundUp((int)szLocalWorkSize[0], width); 
    szGlobalWorkSize[1] = shrRoundUp((int)szLocalWorkSize[1], height);
    int localWidth = BlockDimX + 2;

    errorNum = clSetKernelArg(ckProba, 0, sizeof(cl_mem), (void*) &cmDevBufIn);
    errorNum |= clSetKernelArg(ckProba, 1, sizeof(cl_mem), (void*) &cmDevBufOut);
    errorNum |= clSetKernelArg(ckProba, 2, sizeof(cl_uint), (void*) &width);
    errorNum |= clSetKernelArg(ckProba, 3, sizeof(cl_uint), (void*) &height);
    errorNum |= clSetKernelArg(ckProba, 4, sizeof(cl_uint)*(BlockDimX+2)*(BlockDimY+2), NULL);
    errorNum |= clSetKernelArg(ckProba, 5, sizeof(cl_int), (void*) &localWidth); 

    std::cout << "Running processing\n";
    errorNum = 0; 
    errorNum |= clEnqueueWriteBuffer(commandqueue, cmDevBufIn, CL_FALSE, 0, szBuffBytesout, 
                                       (void*)&uiInputImage[0], 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    errorNum |= clEnqueueNDRangeKernel(commandqueue, ckProba, 2, NULL, szGlobalWorkSize, szLocalWorkSize, 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    errorNum |= clEnqueueReadBuffer(commandqueue, cmDevBufOut, CL_FALSE, 0, szBuffBytesout, (void*)&uiOutputImage[0], 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    if (!errorNum) { 
        std::cout << "clFinish ended succesfully\n";
    } else { 
        std::cout << "clFinish failed\n";
    }



} 

void GrayScale2Bw(cl_uchar * uiInputImage = NULL, cl_uchar * uiOutputImage = NULL, unsigned char threshold = 128) {
    ckProba = clCreateKernel(cpProgram, "GrayScale2BW", &errorNum);
    if (errorNum != CL_SUCCESS)
    {
        shrLog("Error: Failed to create kernel\n");
        exit(0);
    }

    cmDevBufIn = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY, szBuffBytesout, NULL, &errorNum);
    cmDevBufOut = clCreateBuffer(cxGPUContext, CL_MEM_WRITE_ONLY, szBuffBytesout, NULL, &errorNum);
        
    szLocalWorkSize[0] = BlockDimX;
    szLocalWorkSize[1] = BlockDimY;
    szGlobalWorkSize[0] = shrRoundUp((int)szLocalWorkSize[0], width); 
    szGlobalWorkSize[1] = shrRoundUp((int)szLocalWorkSize[1], height);
    //     unsigned int localWidth = BlockDimX + 2;

    errorNum = clSetKernelArg(ckProba, 0, sizeof(cl_mem), (void*) &cmDevBufIn);
    errorNum |= clSetKernelArg(ckProba, 1, sizeof(cl_mem), (void*) &cmDevBufOut);
    errorNum |= clSetKernelArg(ckProba, 2, sizeof(cl_uint), (void*) &width);
    errorNum |= clSetKernelArg(ckProba, 3, sizeof(cl_uint), (void*) &height);
    //    errorNum |= clSetKernelArg(ckProba, 4, sizeof(cl_uint)*(BlockDimX+2)*(BlockDimY+2), NULL);
    //    errorNum |= clSetkernelArg(ckProba, 5, sizeof(cl_uint), (void*) &localWidth); 

    std::cout << "Running processing\n";
    errorNum = 0; 
    errorNum |= clEnqueueWriteBuffer(commandqueue, cmDevBufIn, CL_FALSE, 0, szBuffBytesout, 
                                       (void*)&uiInputImage[0], 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    errorNum |= clEnqueueNDRangeKernel(commandqueue, ckProba, 2, NULL, szGlobalWorkSize, szLocalWorkSize, 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    errorNum |= clEnqueueReadBuffer(commandqueue, cmDevBufOut, CL_FALSE, 0, szBuffBytesout, (void*)&uiOutputImage[0], 0, NULL, NULL);
    errorNum |= clFinish(commandqueue);
    if (!errorNum) { 
        std::cout << "clFinish ended succesfully\n";
    } else { 
        std::cout << "clFinish failed\n";
    }


} 


 

int main(int argc, char** argv) 
{
    errorNum = oclGetPlatformID(&platformId);
    if (errorNum != CL_SUCCESS) { 
        std::cout << "Getting platform IDs were unsuccesfull" << std::endl;
        return -1; 
    } 

    errorNum = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 0, NULL, &deviceCount);
    devices = (cl_device_id *) malloc (sizeof(cl_device_id)); 
    errorNum = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 1, devices, NULL);
    if (errorNum != CL_SUCCESS) { 
        std::cout << "Getting device IDs were unsuccessfull" << std::endl; 
    } else { 
        std::cout << "Getting device IDs were successfull" << std::endl; 
    } 


    
    //cxGPUContext = clCreateContext(0, 1, device, NULL, NULL, &errorNum);
    cxGPUContext = clCreateContext(0, 1, devices, NULL, NULL, &errorNum);
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
    cpProgram = clCreateProgramWithSource(cxGPUContext, 1, (const char **)&source, 
                                                    &program_length, &errorNum);
    if (errorNum != CL_SUCCESS) {
        shrLog("Error: Failed to create program\n");
        return errorNum;
    }

    char *flags = "-cl-fast-relaxed-math";

    errorNum |= clBuildProgram(cpProgram, 0, NULL, flags, NULL, NULL);
    if (errorNum != CL_SUCCESS)
    {
        shrLogEx(LOGBOTH | ERRORMSG, errorNum, STDERROR);
        oclLogBuildInfo(cpProgram, oclGetFirstDev(cxGPUContext));
        oclLogPtx(cpProgram, oclGetFirstDev(cxGPUContext), "Proba.ptx");
        shrLog("Error: Failed to build program\n");
        return errorNum;
    }

    // Allocate per-device OpenCL objects for useful devices

    
    free(header);
    free(source);

    commandqueue = clCreateCommandQueue(cxGPUContext, devices[0] ,0, &errorNum);

    if (argc > 1) { 
        if (loadPPMHeader(argv[1], &width, &height, &channels)) {
            std::cout << "***************************************" << std::endl;
            std::cout << "Image width:  " << width << std::endl;
            std::cout << "Image height: " << height << std::endl;
            std::cout << "Channels: " << channels << std::endl;
            std::cout << "***************************************" << std::endl;
        }
        iGraphicsWinHeight = ((float)height / (float) width) * iGraphicsWinWidth;  // GL Windows height
        
        szBuffBytes = width * height * sizeof (unsigned int) ;
        szBuffBytesout = width * height * sizeof (unsigned char);

        cmPinnedBufIn = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, szBuffBytes, NULL, &errorNum);
        cmPinnedBufOut = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, szBuffBytesout, NULL, &errorNum);
        uiInput = (cl_uint*)clEnqueueMapBuffer(commandqueue, cmPinnedBufIn, CL_TRUE, CL_MAP_WRITE, 0, szBuffBytes, 0, NULL, NULL, &errorNum);
        uiOutput = (cl_uchar *)clEnqueueMapBuffer(commandqueue, cmPinnedBufOut, CL_TRUE, CL_MAP_READ, 0, szBuffBytesout, 0, NULL, NULL, &errorNum);


        cmPinnedBufIn2 = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, szBuffBytesout, NULL, &errorNum);
        cmPinnedBufOut2 = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, szBuffBytesout, NULL, &errorNum);
        uiInput2 = (cl_uchar *)clEnqueueMapBuffer(commandqueue, cmPinnedBufIn2, CL_TRUE, CL_MAP_WRITE, 0, szBuffBytesout, 0, NULL, NULL, &errorNum);
        uiOutput2 = (cl_uchar *)clEnqueueMapBuffer(commandqueue, cmPinnedBufOut2, CL_TRUE, CL_MAP_READ, 0, szBuffBytesout, 0, NULL, NULL, &errorNum);

        cmPinnedBufIn3 = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, szBuffBytesout, NULL, &errorNum);
        cmPinnedBufOut3 = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, szBuffBytesout, NULL, &errorNum);
        uiInput3 = (cl_uchar *)clEnqueueMapBuffer(commandqueue, cmPinnedBufIn3, CL_TRUE, CL_MAP_WRITE, 0, szBuffBytesout, 0, NULL, NULL, &errorNum);
        uiOutput3 = (cl_uchar *)clEnqueueMapBuffer(commandqueue, cmPinnedBufOut3, CL_TRUE, CL_MAP_READ, 0, szBuffBytesout, 0, NULL, NULL, &errorNum);

        
        LoadPPM4ub(argv[1], (unsigned char **) &uiInput, &width, &height); 

        InitGL(&argc, argv);
        glutMainLoop();

    }

    
    

    return 0;
}


void SobelOperator() { 
    
} 

void InitGL(int* argc, char **argv)
{
    // initialize GLUT 
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition (glutGet(GLUT_SCREEN_WIDTH)/2 - iGraphicsWinWidth/2, 
                            glutGet(GLUT_SCREEN_HEIGHT)/2 - iGraphicsWinHeight/2);
    glutInitWindowSize(iGraphicsWinWidth, iGraphicsWinHeight);
    iGLUTWindowHandle = glutCreateWindow("OpenCL for GPU RGB Sobel Filter Demo");

    // register glut callbacks
    glutKeyboardFunc(KeyboardGL);
    glutDisplayFunc(DisplayGL);
    glutReshapeFunc(Reshape);
    glutIdleFunc(Idle);
 
    // Zoom with fixed aspect ratio

    float fAspects[2] = {(float)glutGet(GLUT_WINDOW_WIDTH)/(float)width , (float)glutGet(GLUT_WINDOW_HEIGHT)/(float)height};
    fZoom = fAspects[0] > fAspects[1] ? fAspects[1] : fAspects[0];
    glPixelZoom(fZoom, fZoom);
    //     glewInit();

}

void DisplayGL()
{
    // Run OpenCL kernel to filter image (if toggled on), then render to backbuffer
    if (iProcFlag == 1)
    {
        // process on the GPU or the Host, depending on user toggle/flag
        Rgb2GrayScale(uiInput, uiOutput);

        // Draw processed image
        std::cout << "Maybe before segfault\n";
        unsigned char * mem = new unsigned char[width * height * 4];

        for (unsigned int i = 0; i < width; i++) 
            for (unsigned int j = 0; j < height; j++) {
                mem[(i * height + j) * 4 + 3] = mem[(i * height + j) * 4 + 1] = mem[(i * height + j) * 4 + 2] = mem[(i * height + j) * 4] = uiOutput[(i * height + j)];
                
            }
        std::cout << sizeof(char); 
        //        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        // glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_INT_8_8_8_8, mem); 
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, mem); 
        std::cout << "Maybe after segfault\n";
        delete mem;
    } else if (iProcFlag == 2) {
        Rgb2GrayScale(uiInput, uiOutput);
        memcpy(uiOutput, uiInput2, szBuffBytesout);
        GrayScale2Bw(uiInput2, uiOutput2,threshold );
        std::cout << "Maybe before segfault\n";
        unsigned char * mem = new unsigned char[width * height * 4];

        for (unsigned int i = 0; i < width; i++) 
            for (unsigned int j = 0; j < height; j++) {
                mem[(i * height + j) * 4 + 3] = mem[(i * height + j) * 4 + 1] = mem[(i * height + j) * 4 + 2] = mem[(i * height + j) * 4] = uiOutput2[(i * height + j)];
                
            }
        std::cout << sizeof(char); 
        //         glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, mem); 
        std::cout << "Maybe after segfault\n";
        delete mem;
    } else if (iProcFlag == 3) {
        Rgb2GrayScale(uiInput, uiOutput);
        memcpy(uiOutput, uiInput2, szBuffBytesout);
        GrayScale2Bw(uiInput2, uiOutput2,threshold );
        memcpy(uiOutput2, uiInput3, szBuffBytesout);
        BwFill(uiInput3, uiOutput3); 
        std::cout << "Maybe before segfault\n";
        unsigned char * mem = new unsigned char[width * height * 4];

        for (unsigned int i = 0; i < width; i++) 
            for (unsigned int j = 0; j < height; j++) {
                mem[(i * height + j) * 4 + 3] = mem[(i * height + j) * 4 + 1] = mem[(i * height + j) * 4 + 2] = mem[(i * height + j) * 4] = uiOutput3[(i * height + j)];
                
            }
        std::cout << sizeof(char); 
        //         glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, mem); 
        std::cout << "Maybe after segfault\n";
        delete mem;
        } else  
    {
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, uiInput); 
    }

    //  Flip backbuffer to screen
    glutSwapBuffers();
    glutPostRedisplay();
} 

void Reshape(int /*w*/, int /*h*/)
{
    // Zoom with fixed aspect ratio
    float fAspects[2] = {(float)glutGet(GLUT_WINDOW_WIDTH)/(float)width , (float)glutGet(GLUT_WINDOW_HEIGHT)/(float)height};
    fZoom = fAspects[0] > fAspects[1] ? fAspects[1] : fAspects[0];
    glPixelZoom(fZoom, fZoom);
}

void KeyboardGL(unsigned char key, int /*x*/, int /*y*/)
{
    switch(key) 
    {
        case 'P':   // P toggles Processing between CPU and GPU
        case 'p':   // p toggles Processing between CPU and GPU
            shrLog("Switching processing on or off\n");
            iProcFlag = (iProcFlag + 1) % 4;            
            break;
        case 't': 
            threshold = (threshold +1) % 256;
            break;
        case 'F':   // F toggles main graphics display full screen
        case 'f':   // f toggles main graphics display full screen
            bFullScreen = !bFullScreen;
            if (bFullScreen)
            {
                iGraphicsWinPosX = glutGet(GLUT_WINDOW_X);
                iGraphicsWinPosY = glutGet(GLUT_WINDOW_Y);
                iGraphicsWinWidth = glutGet(GLUT_WINDOW_WIDTH); 
                iGraphicsWinHeight = glutGet(GLUT_WINDOW_HEIGHT);
                glutFullScreen();
            }
            else
            {
                glutReshapeWindow(iGraphicsWinWidth, iGraphicsWinHeight);
                glutPositionWindow(iGraphicsWinPosX, iGraphicsWinPosY);
            }
            shrLog("\nMain Graphics %s...\n", bFullScreen ? "FullScreen" : "Windowed");
            break;
        case '\033':// Escape quits    
        case '\015':// Enter quits    
        case 'Q':   // Q quits
        case 'q':   // q quits
            // Cleanup up and quit
            //            Cleanup(EXIT_SUCCESS);
            exit(0);
            break;
    }

    // Trigger fps update and call for refresh
    glutPostRedisplay();
}

void Idle(void)
{
    glutPostRedisplay();
}
