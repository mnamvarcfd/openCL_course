////////// OpenCL kernel. Each work item takes care of one element of c
__kernel void initDoubleArray(const unsigned int n, __global double* a)
{
    //Get our global thread ID                                
    int i = get_global_id(0);

    //Make sure we do not go out of bounds 
    if (i < n) {
        a[i] = 9.0;
    }

}


__kernel void initIntegerArray(const unsigned int n, __global unsigned int* a)
{                                                             
                              
    unsigned int i = get_global_id(0);                                
                   
    if (i<n) {
        a[i] = 9;
    }

} 


__kernel void multyplyScalarDoubleArray(const unsigned int n, 
 double coeff, __global double* a, __global double* b)
{
    //Get our global thread ID                                
    int i = get_global_id(0);

    //Make sure we do not go out of bounds 
    if (i < n) {
        a[i] = b[i]*coeff;
    }

}

__kernel void addTwoArays(const unsigned int n,
                       __global double *a,                    
                       __global double *b,                   
                       __global double *c                   
                       )                   
{                                                             
                               
    int id = get_global_id(0);                                
                               
    if (id < n)                                                
        c[id] = a[id] + b[id];                                 
} 

__kernel void indirectAdressing(const unsigned int n,__global double *A,__global unsigned int* intA                
                       )                   
{                                                             
                               
    unsigned int i = get_global_id(0);                                
                               
    if (i < n){                                                
        unsigned int pt = intA[i];
        A[pt] = 9.0;    
    }   
                         
} 


__kernel void nestedLoop(const unsigned int nLoop, const unsigned int k, const unsigned int arraySize, __global double* a)
{
 
    unsigned int j = get_global_id(0);

    unsigned int i = k * nLoop + j;

    if (i < arraySize) {
        a[i] = 9.0;
    }

}







double multiplyOperation(double a, double b) {
    return (a * b);
}


__kernel void multiplyTwoArays(const unsigned int n,
                       __global double *a,                    
                       __global double *b,                   
                       __global double *c                   
                       )                   
{                                                             
                               
    int id = get_global_id(0);                                
                               
    if (id < n){                                               
        c[id] = multiplyOperation( a[id] , b[id] ); 
    }
                                
} 

