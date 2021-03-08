// OpenCL kernel. Each work item takes care of one element of c
__kernel void indirectAdressing(const unsigned int nNode, const unsigned int k,
                       __global double* fVal, __global unsigned int* PDFpt 
                     )
{
    unsigned int j = get_global_id(0);

    if (j < nNode) {
        unsigned int i = k * nNode + j;

        unsigned int pt = PDFpt[i];
        fVal[pt] = pt;
    }

}

__kernel void macroCal(const unsigned int nNode, const unsigned int k,
                       __global double* sR, __global double* sU, __global double* sV, 
                       __global double* fVal, __global unsigned int* PDFpt  
                     )
{

    unsigned int j = get_global_id(0);
    if (j < nNode) {
        unsigned int i = k * nNode + j;

        unsigned int pt = PDFpt[i];
        sR[pt] += fVal[i];
        sU[pt] += fVal[i]*2.0;
        sV[pt] += fVal[i]*0.5;
    }

}

__kernel void collision(const unsigned int nNode, const unsigned int k,
                       __global double* R, __global double* U, __global double* V, 
                       __global double* fVal, __global unsigned int* PDFpt  
                     )
{
    unsigned int j = get_global_id(0);
    if (j < nNode) {
        unsigned int i = k * nNode + j;

        unsigned int pt = PDFpt[i];

        double r = R[pt];
        double u = U[pt];
        double v = V[pt];

        fVal[i] += r * (u + v);
    }

}


__kernel void macroFinal(const unsigned int nNode,
                       __global double* sR, __global double* sU, __global double* sV, 
                       __global double* R, __global double* U, __global double* V  
                     )
{
    unsigned int i = get_global_id(0);
    if (i < nNode) {
        R[i] = sR[i]+1;
        U[i] = sU[i]/ R[i];
        V[i] = sV[i]/ R[i];
    }

}

__kernel void readWriteData(const unsigned int nNode, const unsigned int k,
                       __global double* sR, __global double* sU, __global double* sV, 
                       __global double* R, __global double* U, __global double* V, 
                       __global double* fVal, __global unsigned int* PDFpt  
                     )
{
    unsigned int j = get_global_id(0);
    if (j < nNode) {
        unsigned int i = k * nNode + j;

        unsigned int pt = PDFpt[i];
        sR[pt] += R[pt];
        sU[pt] += U[pt];
        sV[pt] += V[pt];

        fVal[i] += 1.0;
    }

}















