//
// Created by collin on 18-12-5.
//

#ifndef SWIG_WRAP_FOR_PYTHON_NUMPY_DATA_H
#define SWIG_WRAP_FOR_PYTHON_NUMPY_DATA_H
#include <Eigen/Dense>
#include <iostream>
#include "CMatrix.hpp"
#include <opencv2/opencv.hpp>



void NUmpyDataCPP2Python(double *mat, int length, crazy::DMatrix &DMat,char *flags);
void NumpyData_Python2CPP(double *mat, int rows, int cols,crazy::DMatrix &DMat);
void Image_Python2CPP(double *mat, int rows, int cols,int c,crazy::ImageMatrix &ImageMat);
void ImageMatrixCPP2Python(double *mat, int length,crazy::ImageMatrix &imgMat, int c,char *flags);




#endif //SWIG_WRAP_FOR_PYTHON_NUMPY_DATA_H
