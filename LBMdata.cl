
////////// OpenCL kernel. Each work item takes care of one element of c
__kernel void Comput(const unsigned int n,
                     __global double* R, __global double* U, __global double* V, 
                     __global double* sR, __global double* sU, __global double* sV, 
                     __global double* fVal, __global unsigned int* PDFpt  
                     )
{
    //Get our global thread ID                                
    int i = get_global_id(0);

    //Make sure we do not go out of bounds 
    if (i < n) {
        sR[i] += R[i];
        sU[i] += U[i];
        sV[i] += V[i];

        unsigned int pt = PDFpt[i];
        fVal[pt] += 1.0;
    }

}
