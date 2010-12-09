
__kernel void MorphFill(__global const uchar * in, 
                       __global uchar * out,
                       unsigned int imageWidth, 
                       unsigned int imageHeight, 
                       __local  uchar * localData, 
                       int localWidth) { 

    // Block index
    int bx  = get_global_id(0); 
    int by  = get_global_id(1) -1 ; // felfele tolas egye sorral
    
    int GlobalMemOffset = mul24(by, (int) imageWidth) + bx;
    int LocalMemOffset = mul24((int) get_local_id(1), localWidth) + get_local_id(0) + 1;
    
    if( (by >= 0) && (by < imageHeight) && (bx < imageWidth))
        {
            localData[LocalMemOffset] = in[GlobalMemOffset];
        } else { 
        localData[LocalMemOffset] = 0;
    } 
    
    // also ketto bemasolja a legutolso 2 sort is
    if (get_local_id(1) < 2) {
        LocalMemOffset += mul24((int) get_local_size(1), localWidth);
        if (((by +  get_local_size(1)) < imageHeight) && (bx < imageWidth))
            localData[LocalMemOffset] = in[GlobalMemOffset + mul24(get_local_size(1), imageWidth)];
        else 
            localData[LocalMemOffset] = (uchar) 0;
    }
    
    // jobb szele
    if (get_local_id(0) == (get_local_size(0) -1)) {
        
        LocalMemOffset = mul24((int) get_local_id(1), localWidth);
        if ((by >= 0) && (by < imageHeight) && (get_group_id(0) > 0))
            localData[LocalMemOffset] = in[mul24(by, (int) imageWidth) + 
                                           mul24(get_group_id(0), imageWidth) -1];
        else 
            localData[LocalMemOffset] = (uchar) 0;
        
        // also ket sor a blokkban
        if(get_local_id(1) < 2) {
            LocalMemOffset += mul24((int) get_local_size(1), localWidth);
            
            if (((by +  get_local_size(1)) < imageHeight) && (get_group_id(0) > 0))
                localData[LocalMemOffset] = in[mul24((by + (int) get_local_size(1)), (int) imageWidth) + mul24(get_group_id(0), get_local_size(0)) -1];
            else 
                localData[LocalMemOffset] = (uchar) 0;
        } 
    } else if (get_local_id(0) == 0) {
        LocalMemOffset = mul24(((int) get_local_id(1) + 1), localWidth) - 1;
        if ((by >= 0) && (by < imageHeight) && (mul24(((int) get_group_id(0) +1), (int) get_local_size(0)) < imageWidth)) { 
            localData[LocalMemOffset] = in[mul24(by, (int) imageWidth) + mul24((get_group_id(0) + 1), get_local_size(0))];
        } else { 
            localData[LocalMemOffset] = 0;
        }
        
        
        if (get_local_id(1) < 2) {
            LocalMemOffset += mul24((int) get_local_size(1), localWidth);
            if (((by + get_local_size(1)) < imageHeight) && (mul24((get_group_id(0) +1), get_local_size(0)) < imageWidth)) {
                localData[LocalMemOffset] = in[mul24((by + (int) get_local_size(1)), (int) imageWidth) + mul24((get_group_id(0) + 1), get_local_size(0))];
            } else {
                localData[LocalMemOffset] = 0; 
            }
        }                    
    }
    
    // Block index
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    LocalMemOffset = mul24((int)get_local_id(1) + 1, localWidth) + get_local_id(0) + 1 ;
    
    unsigned char temp = 0x00; 
    temp = temp | localData[LocalMemOffset - localWidth] 
        | localData[LocalMemOffset - 1] 
        | localData[LocalMemOffset ] 
        | localData[LocalMemOffset + 1] 
        | localData[LocalMemOffset + localWidth];

    out[GlobalMemOffset] = temp;
} 

__kernel void MorphFit(__global const uchar * in, 
                       __global uchar * out,
                       unsigned int imageWidth, 
                       unsigned int imageHeight, 
                       __local  uchar * localData, 
                       int localWidth) { 


              // Block index
              int bx  = get_global_id(0); 
              int by  = get_global_id(1) -1 ; // felfele tolas egye sorral

              int GlobalMemOffset = mul24(by, (int) imageWidth) + bx;
              int LocalMemOffset = mul24((int) get_local_id(1), localWidth) + get_local_id(0) + 1;

              if( (by >= 0) && (by < imageHeight) && (bx < imageWidth))
              {
                  localData[LocalMemOffset] = in[GlobalMemOffset];
              } else { 
                  localData[LocalMemOffset] = 0;
              } 

              // also ketto bemasolja a legutolso 2 sort is
              if (get_local_id(1) < 2) {
                  LocalMemOffset += mul24((int) get_local_size(1), localWidth);
                  if (((by +  get_local_size(1)) < imageHeight) && (bx < imageWidth))
                      localData[LocalMemOffset] = in[GlobalMemOffset + mul24(get_local_size(1), imageWidth)];
                  else 
                      localData[LocalMemOffset] = (uchar) 0;
              }

              // jobb szele
              if (get_local_id(0) == (get_local_size(0) -1)) {

                  LocalMemOffset = mul24((int) get_local_id(1), localWidth);
                  if ((by >= 0) && (by < imageHeight) && (get_group_id(0) > 0))
                      localData[LocalMemOffset] = in[mul24(by, (int) imageWidth) + 
                                                     mul24(get_group_id(0), imageWidth) -1];
                  else 
                      localData[LocalMemOffset] = (uchar) 0;

                  // also ket sor a blokkban
                  if(get_local_id(1) < 2) {
                      LocalMemOffset += mul24((int) get_local_size(1), localWidth);

                      if (((by +  get_local_size(1)) < imageHeight) && (get_group_id(0) > 0))
                          localData[LocalMemOffset] = in[mul24((by + (int) get_local_size(1)), (int) imageWidth) + mul24(get_group_id(0), get_local_size(0)) -1];
                      else 
                          localData[LocalMemOffset] = (uchar) 0;
                  } 
              } else if (get_local_id(0) == 0) {
                  LocalMemOffset = mul24(((int) get_local_id(1) + 1), localWidth) - 1;
                  if ((by >= 0) && (by < imageHeight) && (mul24(((int) get_group_id(0) +1), (int) get_local_size(0)) < imageWidth)) { 
                      localData[LocalMemOffset] = in[mul24(by, (int) imageWidth) + mul24((get_group_id(0) + 1), get_local_size(0))];
                  } else { 
                      localData[LocalMemOffset] = 0;
                  }


                  if (get_local_id(1) < 2) {
                      LocalMemOffset += mul24((int) get_local_size(1), localWidth);
                      if (((by + get_local_size(1)) < imageHeight) && (mul24((get_group_id(0) +1), get_local_size(0)) < imageWidth)) {
                          localData[LocalMemOffset] = in[mul24((by + (int) get_local_size(1)), (int) imageWidth) + mul24((get_group_id(0) + 1), get_local_size(0))];
                      } else {
                          localData[LocalMemOffset] = 0; 
                      }
                  }                    
              }

              // Block index
              
              barrier(CLK_LOCAL_MEM_FENCE);

              LocalMemOffset = mul24((int)get_local_id(1) + 1, localWidth) + get_local_id(0) + 1 ;

              // mas mas strukturalo elem de a memoriamasolas ugyanaz kell legyen :-)
              // #ifdef DISK_KERNEL
              // out[GlobalMemOffset] = localData[LocalMemOffset];

              unsigned char temp = 0xFF; 
              /*              temp &= localData[LocalMemOffset - localWidth];  
              temp &= localData[LocalMemOffset - 1];
              temp &= localData[LocalMemOffset ];
              temp &= localData[LocalMemOffset + 1];
              temp &= localData[LocalMemOffset + localWidth]; */
              temp = temp & localData[LocalMemOffset - localWidth] 
                          & localData[LocalMemOffset - 1] 
                          & localData[LocalMemOffset ] 
                          & localData[LocalMemOffset + 1] 
                          & localData[LocalMemOffset + localWidth];

              out[GlobalMemOffset] = temp;
              // #else 
             // #endif         
}

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
