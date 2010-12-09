/* And we have an empty kernel code here */

#define i

__kernel void MorphFill(__global const float * in, 
              __global       float * out) { 

              // Block index
              int bx  = get_group_id(0); 
              int by  = get_group_id(1);

              // Thread index 
              
              int tx = get_local_id(0); 
              int ty = get_local_id(1);

              int index = bx * 10 + by;

              out[index] = in[index];
} 

/* __kernel void MorphFit(__global const uchar4 * in, 
                            __global uchar4 * out,
                            unsigned int imageWidth, 
                            unsigned int imageHeight) { 

              // Block index
              int bx  = get_global_id(0); 
              int by  = get_global_id(1) -1;

              int lx = get_local_id(0); 
              int ly = get_local_id(1);              

              int memoffset = mul24(by, (int) get_global_size(0)) + bx;

              if((by >= 0) && (by < imageHeight) && (bx < imageWidth))
                  {
                      uc4LocalData[iLocalPixOffset] = uc4Source[iDevGMEMOffset];
                  }
              else 
                  {
                      uc4LocalData[iLocalPixOffset] = (uchar4)0; 
                  }
              
              barrier(CLK_LOCAL_MEM_FENCE);

              // mas mas strukturalo elem de a memoriamasolas ugyanaz kell legyen :-)
#ifdef DISK_KERNEL
              out[index] = in[index] 
#else 

#endif            
              out[index] = in[index];
} */

__kernel void Rgb2GrayScale(__global const uchar4 * in, 
                            __global uchar * out,
                            unsigned int imageWidth, 
                            unsigned int imageHeight) 
{ 
              // Block index
              int bx  = get_global_id(0); 
              int by  = get_global_id(1);

              //              int memoffset = mul24(by, (int) get_global_size(0)) + bx;
              int memoffset = mul24(by, (int) imageWidth) + bx;

              if((by >= imageHeight) || (bx >= imageWidth))
              {
                  return;
              } else { 
                  float v =                   
                      (float) in[memoffset].x * 0.3f + 
                      (float) in[memoffset].y * 0.59f + 
                      (float) in[memoffset].z * 0.11f;                                        
                  
                  unsigned char uiPackedPix = 0x00;
                  uiPackedPix |= 0xFF & (((unsigned int)v));
                  out[memoffset] = uiPackedPix;
              }
}

__kernel void GrayScale2BW(__global const uchar * in, 
                           __global uchar * out,
                           unsigned int imageWidth, 
                           unsigned int imageHeight, 
                           unsigned char threshold) { 

              int bx  = get_global_id(0); 
              int by  = get_global_id(1);

              int memoffset = mul24(by, (int) get_global_size(0)) + bx;

              if((by >= imageHeight) || (bx >= imageWidth))
              {
                  return;
              } else {                                     
                  if (in[memoffset] > threshold) 
                      out[memoffset] = 0xFF;
                  else 
                      out[memoffset] = 0x00;
              }
} 
