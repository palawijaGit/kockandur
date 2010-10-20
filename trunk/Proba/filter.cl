/* And we have an empty kernel code here */

#define i

__kernel void
SobelOperator(_global const float * in, 
              _global       float * out) { 

              // Block index
              int bx  = get_group_id(0); 
              int by  = get_group_id(1);

              // Thread index 
              
              int tx = get_local_id(0); 
              int ty = get_local_id(1);

              out[index] = in[index];
} 