
// OpenCL kernel. Each work item takes care of one element of c
__kernel void comput(const unsigned int n, __global double *fVal)                   
{                                                             
                   
    int i = get_global_id(0);   
                 
    if (i < n) {   
        fVal[i] = 1.0;
    }  
                             
}    



// OpenCL kernel. Each work item takes care of one element of c
__kernel void comput3(const unsigned int n,
                     __global double *fVal,                    
                     __global int *PDFpt)                   
{                                                             
    //Get our global thread ID                                
    int i = get_global_id(0);                                
                                                               
    //Make sure we do not go out of bounds                    
    if (i < n) {   
        fVal[i] = 1.0;
    }                               
}    


// OpenCL kernel. Each work item takes care of one element of c
__kernel void comput2(const unsigned int n,
                     __global double *fVal,                    
                     __global unsigned int *PDFpt)                   
{                                                             
    //Get our global thread ID                                
    int i = get_global_id(0);                                
                                                               
    //Make sure we do not go out of bounds                    
    if (i < n) {      
        unsigned int pt = PDFpt[i];
        fVal[pt] += 1.0;
    }                               
}                                                              
  