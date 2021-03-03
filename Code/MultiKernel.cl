
////////// OpenCL kernel. Each work item takes care of one element of c
__kernel void kernel1(__global double* a, const unsigned int n)
{
    //Get our global thread ID                                
    int i = get_global_id(0);

    //Make sure we do not go out of bounds 
    if (i < n) {
        double val = (double)i;
        double val2 = val + 1 + 2 * val - 16 * val - 6 * val - 3;
        val2 = val2 + val + 2 + 3 * val + 4 * val - 2 * val - 1;
        val2 = val2 + val + 6 + 5 * val + 6 * val - 8 * val - 4;
        val2 = val2 + val + 1 + 6 * val + 7 * val - 4 * val - 2;
        a[i] = val2;;
    }

}


__kernel void kernel2(  __global double *a, const unsigned int n)
{                                                             
    //Get our global thread ID                                
    int i = get_global_id(0);                                
                                                               
    //Make sure we do not go out of bounds 
    if (i<n) {
        a[i] = 1024;
    }

} 