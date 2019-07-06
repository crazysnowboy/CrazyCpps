//
// Created by collin on 18-12-5.
//

#include "numpy_data.h"


void NUmpyDataCPP2Python(double *mat, int length,crazy::DMatrix &DMat, char *flags)
{


    std::string flags_str = flags;
    int mat_rows =DMat.rows();
    int mat_cols =DMat.cols();

    if(flags_str == "GetLength")
    {
        mat[0]=(double)mat_rows;
        mat[1]=(double)mat_cols;
    }
    if(flags_str == "GetData")
    {

        for(int row_i=0; row_i<mat_rows; row_i++)
        {
            for(int col_i=0; col_i<mat_cols; col_i++)
            {
                mat[row_i*mat_cols + col_i] = DMat.Get(row_i,col_i);
            }
        }

    }


}
void NumpyData_Python2CPP(double *mat, int rows, int cols,crazy::DMatrix &DMat)
{


    DMat.Create(rows,cols,0.0);

    for(int row_i=0;row_i<rows;row_i++)
    {
        for(int col_i=0; col_i<cols; col_i++)
        {

            DMat.Set(row_i,col_i,mat[row_i*cols+col_i]);

//            std::cout <<" "<<mat[j*cols+i]<<" ";

        }
//        std::cout <<std::endl;
    }

}

void Image_Python2CPP(double *mat, int rows, int cols,int c,crazy::ImageMatrix &ImageMat)
{


    if(c==0)
    {
        ImageMat.Create(rows,cols,3,0.0);
    }

    for(int row_i=0;row_i<rows;row_i++)
    {
        for(int col_i=0; col_i<cols; col_i++)
        {
            ImageMat.Set(row_i,col_i,c,mat[row_i*cols+col_i]);

        }
    }


}


void ImageMatrixCPP2Python(double *mat, int length,crazy::ImageMatrix &imgMat,int c, char *flags)
{


    std::string flags_str = flags;
    int mat_rows =imgMat.rows();
    int mat_cols =imgMat.cols();

    if(flags_str == "GetLength")
    {
        mat[0]=(double)mat_rows;
        mat[1]=(double)mat_cols;
    }
    if(flags_str == "GetData")
    {

        for(int row_i=0; row_i<mat_rows; row_i++)
        {
            for(int col_i=0; col_i<mat_cols; col_i++)
            {
                mat[row_i*mat_cols + col_i] = imgMat.Get(row_i,col_i,c);

            }
        }

    }


}