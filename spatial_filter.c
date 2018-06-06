#include <stdio.h>
#include <mex.h>

void spatial_filter(double *img_in , double *k_in , double *img_out, int img_h, int img_w, int k_h, int k_w){
    int i, j, k_i, k_j;
    int row, col = 0;    
    double s;
    const int k_r = k_h;
    const int k_c = k_w;
    const int img_r = img_h;
	const int img_c = img_w;
    const int k_middle_r = k_r/2;
    const int k_middle_c = k_c/2;
    double k[k_r][k_c];
    double tmp[k_r][k_c];
    double img[img_r][img_c];
    double img_tmp[img_r][img_c];
        
    for (i=0; i< k_r*k_c; i++){
        row = (k_r - 1) - (i % k_r);
        col= (k_c - 1) - (i / k_c);
        k[row][col] = k_in[i];
    }
    
    for (i=0; i< img_r*img_c; i++){
        row = i % img_r;
        col = i / img_r;
        img[row][col] = img_in[i];
    }
    
    for (i=0; i<img_r; i++){
        for (j=0; j<img_c; j++){
           
            for (k_i=0; k_i<k_r; k_i++){
                for (k_j=0; k_j<k_c; k_j++){
                    col = j-(k_middle_c-k_j);
                    row = i-(k_middle_r-k_i);
                    
                    if (col<0 && row>=0 && row<img_r){
                        tmp[k_i][k_j] = img[row][0];
                    }else if ( col>=img_c && row>=0 && row<img_r){
                        tmp[k_i][k_j] = img[row][img_c-1];
                     
                    }else if ( row<0 && col>=0 && col<img_c){
                        tmp[k_i][k_j] = img[0][col];
                        
                    }else if ( row>=img_r && col>=0 && col<img_c){
                        tmp[k_i][k_j] = img[img_r-1][col];
                    
                    }else if (row<0 && col<0){
                        tmp[k_i][k_j] = img[0][0];
                       
                    }else if (row<0 && col>=img_c){
                        tmp[k_i][k_j] = img[0][img_c-1];
                       
                    }
                    
                    else if (row>=img_r && col<0){
                        tmp[k_i][k_j] = img[img_r-1][0];
                      
                    }else if (row>=img_r && col>=img_c){
                        tmp[k_i][k_j] = img[img_r-1][img_c-1];
                        
                    }else{
                        tmp[k_i][k_j] = img[row][col];
                    }
                }
            }
            
           
            s = 0;
            for (k_i=0; k_i<k_r; k_i++){
                for (k_j=0; k_j<k_c; k_j++){
                    s += k[k_i][k_j] * tmp[k_i][k_j];
                }
            }
            img_tmp[i][j] = s;
        }
    }
    
  
    for (i=0; i<img_r*img_c; i++){
        row = i % img_r;
        col = i / img_r;
        img_out[i] = img_tmp[row][col];
    }
    

}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *img_in_m;
    mxArray *k_in_m;
    mxArray *img_out_m;
    double *img_in;
    double *k_in;
	double *img_out;
    img_in_m = mxDuplicateArray(prhs[0]);
    k_in_m = mxDuplicateArray(prhs[1]);
    const mwSize *img_dims = mxGetDimensions(prhs[0]);
    int img_h = (int)img_dims[0];
    int img_w = (int)img_dims[1];
    const mwSize *k_dims = mxGetDimensions(prhs[1]);
    int k_h = (int)k_dims[0];
    int k_w = (int)k_dims[1];
    img_out_m = plhs[0] = mxCreateNumericArray (2, img_dims, mxDOUBLE_CLASS, mxREAL);
    img_in = (double*)mxGetData(img_in_m);
    k_in = (double*)mxGetData(k_in_m);
    img_out = (double*)mxGetData(img_out_m);
    
	spatial_filter(img_in, k_in, img_out, img_h, img_w, k_h, k_w);

	return;
}