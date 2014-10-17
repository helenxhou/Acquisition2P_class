/* C file autogenerated by mexme.m */
#include <mex.h>
#include <math.h>
#include <matrix.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

/* Translate matlab types to C */
#define uint64 unsigned long int
#define int64 long int
#define uint32 unsigned int
#define int32 int
#define uint16 unsigned short
#define int16 short
#define uint8 unsigned char
#define int8 char
#define single float

#include "mexmetypecheck.cpp"

/* Your extra includes and function definitions here */


double bin0(const double *knots,int ii,int n,double x)
{
    return x < knots[ii+1] && x >= knots[ii];
}

double bin1(const double *knots,int ii,int n,double x)
{
    double delta = 1e-8;
    if (x<knots[ii+1] && x>= knots[ii])
        return (x-knots[ii])/(delta + knots[ii+1]-knots[ii]);
    else if(x<knots[ii+2] && x>= knots[ii+1])
        return (knots[ii+2] - x)/(delta + knots[ii+2]-knots[ii+1]);
}

double bin2(const double *knots,int ii,int n,double x)
{
    double delta = 1e-8;
    double m = (x<knots[ii+2] && x>= knots[ii+1]);
    if(m)
    {
        return (x-knots[ii])/(knots[ii+2]-knots[ii]+delta)*((knots[ii+2] - x)/(delta + knots[ii+2]-knots[ii+1])) + 
               (knots[ii+3] - x)/(knots[ii+3]-knots[ii+1]+delta)*(x-knots[ii+1])/(delta + knots[ii+2]-knots[ii+1]);
    }
    else if(x<knots[ii+1] && x>= knots[ii])
    {
        return (x-knots[ii])*(x-knots[ii])/((knots[ii+2]-knots[ii]+delta)*(delta + knots[ii+1]-knots[ii]));
    }
    else if(x<knots[ii+3] && x>= knots[ii+2])
    {
        return (knots[ii+3] - x)/(knots[ii+3]-knots[ii+1]+delta)*(knots[ii+3] - x)/(delta + knots[ii+3]-knots[ii+2]);
    }
    return 0;
    /*
    return (x-knots[ii])/(knots[ii+2]-knots[ii]+delta)*(  
            (x-knots[ii])/(delta + knots[ii+1]-knots[ii])* + 
            (knots[ii+2] - x)/(delta + knots[ii+2]-knots[ii+1])*m) + 
        (knots[ii+3] - x)/(knots[ii+3]-knots[ii+1]+delta)*(
            (x-knots[ii+1])/(delta + knots[ii+2]-knots[ii+1])*m + 
            (knots[ii+3] - x)/(delta + knots[ii+3]-knots[ii+2])*(x<knots[ii+3] && x>= knots[ii+2]));
     **/
}


double bin(const double *knots,int ii,int n,double x)
{
    double delta = 1e-8;
    if(n == 0)
    {
        return bin0(knots,ii,n,x);
    }
    else if(n == 1)
    {
        return bin1(knots,ii,n,x);
    }
    else if(n == 2)
    {
        return bin2(knots,ii,n,x);
    }
    else
    {
        return (x-knots[ii])/(knots[ii+n]-knots[ii]+delta)*bin(knots,ii,n-1,x) + 
            (knots[ii+n+1] - x)/(knots[ii+n+1]-knots[ii+1]+delta)*bin(knots,ii+1,n-1,x);
    }
}

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{

/*Input output boilerplate*/
    if(nlhs != 1 || nrhs != 6)
        mexErrMsgTxt("Function must be called with 6 arguments and has 1 return values");

    const mxArray *x_ptr = prhs[0];
    mexmetypecheck(x_ptr,mxDOUBLE_CLASS,"Argument x (#1) is expected to be of type double");
    const mwSize   x_m = mxGetM(x_ptr);
    const mwSize   x_n = mxGetN(x_ptr);
    const mwSize   x_length = x_m == 1 ? x_n : x_m;
    const mwSize   x_numel = mxGetNumberOfElements(x_ptr);
    const int      x_ndims = mxGetNumberOfDimensions(x_ptr);
    const mwSize  *x_size = mxGetDimensions(x_ptr);
    const double  *x = (double *) mxGetData(x_ptr);
    const mxArray *firstknot_ptr = prhs[1];
    mexmetypecheck(firstknot_ptr,mxDOUBLE_CLASS,"Argument firstknot (#2) is expected to be of type double");
    const mwSize   firstknot_m = mxGetM(firstknot_ptr);
    const mwSize   firstknot_n = mxGetN(firstknot_ptr);
    const mwSize   firstknot_length = firstknot_m == 1 ? firstknot_n : firstknot_m;
    const mwSize   firstknot_numel = mxGetNumberOfElements(firstknot_ptr);
    const int      firstknot_ndims = mxGetNumberOfDimensions(firstknot_ptr);
    const mwSize  *firstknot_size = mxGetDimensions(firstknot_ptr);
    const double  *firstknot = (double *) mxGetData(firstknot_ptr);
    const mxArray *lastknot_ptr = prhs[2];
    mexmetypecheck(lastknot_ptr,mxDOUBLE_CLASS,"Argument lastknot (#3) is expected to be of type double");
    const mwSize   lastknot_m = mxGetM(lastknot_ptr);
    const mwSize   lastknot_n = mxGetN(lastknot_ptr);
    const mwSize   lastknot_length = lastknot_m == 1 ? lastknot_n : lastknot_m;
    const mwSize   lastknot_numel = mxGetNumberOfElements(lastknot_ptr);
    const int      lastknot_ndims = mxGetNumberOfDimensions(lastknot_ptr);
    const mwSize  *lastknot_size = mxGetDimensions(lastknot_ptr);
    const double  *lastknot = (double *) mxGetData(lastknot_ptr);
    const mxArray *knots_ptr = prhs[3];
    mexmetypecheck(knots_ptr,mxDOUBLE_CLASS,"Argument knots (#4) is expected to be of type double");
    const mwSize   knots_m = mxGetM(knots_ptr);
    const mwSize   knots_n = mxGetN(knots_ptr);
    const mwSize   knots_length = knots_m == 1 ? knots_n : knots_m;
    const mwSize   knots_numel = mxGetNumberOfElements(knots_ptr);
    const int      knots_ndims = mxGetNumberOfDimensions(knots_ptr);
    const mwSize  *knots_size = mxGetDimensions(knots_ptr);
    const double  *knots = (double *) mxGetData(knots_ptr);
    const mxArray *weights_ptr = prhs[4];
    mexmetypecheck(weights_ptr,mxDOUBLE_CLASS,"Argument weights (#5) is expected to be of type double");
    const mwSize   weights_m = mxGetM(weights_ptr);
    const mwSize   weights_n = mxGetN(weights_ptr);
    const mwSize   weights_length = weights_m == 1 ? weights_n : weights_m;
    const mwSize   weights_numel = mxGetNumberOfElements(weights_ptr);
    const int      weights_ndims = mxGetNumberOfDimensions(weights_ptr);
    const mwSize  *weights_size = mxGetDimensions(weights_ptr);
    const double  *weights = (double *) mxGetData(weights_ptr);
    const mxArray *order_ptr = prhs[5];
    mexmetypecheck(order_ptr,mxDOUBLE_CLASS,"Argument order (#6) is expected to be of type double");
    if(mxGetNumberOfElements(order_ptr) != 1)
        mexErrMsgTxt("Argument order (#6) must be scalar");
    const double   order = (double) mxGetScalar(order_ptr);
    

    mwSize Sx_dims[] = {x_numel,weights_length};
    plhs[0] = mxCreateNumericArray(2,Sx_dims,mxDOUBLE_CLASS,mxREAL);
    mxArray **Sx_ptr = &plhs[0];
    double   *Sx = (double *) mxGetData(*Sx_ptr);
    


/*Actual function*/
#include "evalBin.snip.cpp"


}

