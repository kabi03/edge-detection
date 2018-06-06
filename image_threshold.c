#include <stdio.h>
#include <mex.h>


void img_threshold(double *img_in , double *img_out, int img_h, int img_w, double threshold){
    int i;
    
    for ( i=0; i< img_h*img_w; i++){
        if ( img_in[i] < threshold){
            img_out[i] = 0;
        }else{
            img_out[i] = 1;
        }
    }
}



void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *img_in_m;
    mxArray *img_out_m;
    double *img_in;
	double *img_out;
    double threshold;
    img_in_m = mxDuplicateArray(prhs[0]);
    threshold = mxGetScalar(prhs[1]);
    const mwSize *img_dims = mxGetDimensions(prhs[0]);
    int img_h = (int)img_dims[0];
    int img_w = (int)img_dims[1];
    img_out_m = plhs[0] = mxCreateNumericArray (2, img_dims, mxDOUBLE_CLASS, mxREAL);
    img_in = (double*)mxGetData(img_in_m);
    img_out = (double*)mxGetData(img_out_m);
    
	img_threshold(img_in, img_out, img_h, img_w, threshold);

	return;
}