#include <stdio.h>
#include <mex.h>

void non_max_suppress(double *img_in , double *img_out, int img_h, int img_w, double win_h, double win_w ){
    int i, j, k;
    int row, col = 0;
    const int img_r = img_h;
	const int img_c = img_w;
    const int nms_win_h = (int)win_h;
    const int nms_win_w = (int)win_w;
    double img[img_r][img_c];
    double img_tmp_h[img_r][img_c];
    double img_tmp_v[img_r][img_c];
    double horz_win[nms_win_w];
    double vert_win[nms_win_h];
    
    for ( i=0; i< img_r*img_c; i++ ){
        row = i % img_r;
        col = i / img_r;
        img[row][col] = img_in[i];
    }
    
    for ( i=0; i<img_r; i++ ){
        for ( j=0; j<img_c; j++ ){
           
            for ( k=0; k<nms_win_w; k++ ){
                col = j-(nms_win_w/2-k);
                
                if ( col < 0 ){
                    horz_win[k] = img[i][0];
                }else if ( col >= img_c ){
                    horz_win[k] = img[i][img_c-1];
                }else{
                     horz_win[k] = img[i][col];
                }
            }
            
            for ( k=0; k<nms_win_w; k++ ){
                if ( img[i][j] < horz_win[k] ){
                    img_tmp_h[i][j] = 0;
                    break;
                }else{
                    img_tmp_h[i][j] = img[i][j];
                }
            }
        }
    }
   
    for ( j=0; j<img_c; j++){
        for ( i=0; i<img_r; i++){
            for ( k=0; k<nms_win_h; k++ ){
                row = i-(nms_win_h/2-k);
                
                if ( row < 0 ){
                    vert_win[k] = img_tmp_h[i][0];
                }else if ( row >= img_r ){
                    vert_win[k] = img_tmp_h[i][img_r-1];
                }else{
                     vert_win[k] = img_tmp_h[row][j];
                }
            }
            
            
            for ( k=0; k<nms_win_h; k++){
                if ( img_tmp_h[i][j] < vert_win[k] ){
                    img_tmp_v[i][j] = 0;
                    break;
                }else{
                    img_tmp_v[i][j] = img_tmp_h[i][j];
                }
            }
        }
    }
    
   
    for ( i=0; i<img_r*img_c; i++ ){
        row = i % img_r;
        col = i / img_r;
        img_out[i] = img_tmp_v[row][col];
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *img_in_m;
    mxArray *img_out_m;
    double *img_in;
	double *img_out;
    double win_h;
    double win_w;
    img_in_m = mxDuplicateArray(prhs[0]);
    win_h = mxGetScalar(prhs[1]);
    win_w = mxGetScalar(prhs[2]);
    const mwSize *img_dims = mxGetDimensions(prhs[0]);
    int img_h = (int)img_dims[0];
    int img_w = (int)img_dims[1];
    img_out_m = plhs[0] = mxCreateNumericArray (2, img_dims, mxDOUBLE_CLASS, mxREAL );
    img_in = (double*)mxGetData(img_in_m);
    img_out = (double*)mxGetData(img_out_m);
    
	non_max_suppress(img_in, img_out, img_h, img_w, win_h, win_w);

	return;
}