// OpenCL kernel. Each work item takes care of one element of c
__kernel void Shift(  __global double *a, const unsigned int n, int lengt)
{                                                             
    //Get our global thread ID                                
    int id = get_global_id(0);                                
                                                               
    //Make sure we do not go out of bounds 
    for (int i = lengt; i > 0; i--) {
        int arg = id * lengt + i;
        if (0 < arg && arg<n) {
            a[arg] = a[arg -1] * (sqrt(1.0) * sqrt(1.0) * sqrt(n / 3.0)) / sqrt(n / 3.0);
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
            //a[arg] = sqrt(1.0) * sqrt(1.0) * sqrt(1.0) * sqrt(3.0) / sqrt(3.0) * a[arg];
        }
    }
}                                                              
  


//more comput : OpenCL = 0.021  / C++ = 0.4      =====> speed up = 190
//less comput : OpenCL = 0.021  / C++ = 0.001    =====> speed up = 0.047