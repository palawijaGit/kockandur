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

__kernel void MorphFit(__global const uchar4 * in, 
                            __global uchar4 * out,
                            unsigned int imageWidth, 
                            unsigned int imageHeight) { 

              // Block index
              int bx  = get_global_id(0); 
              int by  = get_global_id(1);

              int memoffset = mul24(by, (int) get_global_size(0)) + bx;

              out[index] = in[index];
}

__kernel void Rgb2GrayScale(__global const uchar4 * in, 
                            __global uchar4 * out,
                            unsigned int imageWidth, 
                            unsigned int imageHeight) 
{ 
              // Block index
              int bx  = get_global_id(0); 
              int by  = get_global_id(1);

              int memoffset = mul24(by, (int) get_global_size(0)) + bx;

              if((by >= imageHeight) || (bx >= imageWidth))
              {
                  return;
              } else { 
                  float v =                   
                      (float) in[memoffset].x * 0.3f + 
                      (float) in[memoffset].y * 0.59f + 
                      (float) in[memoffset].z * 0.11f;                                        
                  
                  unsigned int uiPackedPix = 0x00000000;
                  uiPackedPix |= 0x000000FF & (((unsigned int)v));
                  uiPackedPix |= 0x0000FF00 & (((unsigned int)v) << 8);
                  uiPackedPix |= 0x00FF0000 & (((unsigned int)v) << 16);
//                  uiPackedPix |= 0xFF000000 & (((unsigned int)v) << 24);                  
                  out[memoffset] = uiPackedPix;
              }
}

__kernel void GrayScale2BW(__global const float * in, 
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
