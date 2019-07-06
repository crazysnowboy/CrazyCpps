//
// Created by collin on 18-11-23.
//

#ifndef CRAZY_CRAZY_TOOLS_H
#define CRAZY_CRAZY_TOOLS_H

#include <opencv2/opencv.hpp>
#include "CMatrix.hpp"
namespace Tool
{
cv::Mat convert_ImageMatrix2CVImage(crazy::ImageMatrix in_image);
crazy::ImageMatrix convert_CVImage2ImageMatrix(cv::Mat in_image);

crazy::DMatrix CvtCVMat2DMatrix(cv::Mat mat);
cv::Mat CvtDMatrix2CVMat(crazy::DMatrix mat);

crazy::DMatrix CvtEigenTriplets2DMatrix(ArrayTriplet triplet);
ArrayTriplet CvtDMatrix2EigenTriplets(crazy::DMatrix DMat);

}

#endif //CRAZY_CRAZY_TOOLS_H
