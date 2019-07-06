//
// Created by collin on 18-11-23.
//
#include "crazy_tools.h"
namespace Tool
{

cv::Mat convert_ImageMatrix2CVImage(crazy::ImageMatrix in_image)
{


    cv::Mat image_src(in_image.rows(),in_image.cols(),CV_64FC(in_image.chanels()));
    for(int row_i=0; row_i<image_src.rows; row_i++)
    {
        for(int col_i=0; col_i<image_src.cols; col_i++)
        {

            if(in_image.chanels()==3)
            {
                for(int c =0; c<in_image.chanels(); c++)
                {
                    image_src.at<cv::Vec3d>(row_i,col_i)[c] = in_image.Get(row_i,col_i,c);
                }

            }
            else if(in_image.chanels()==4)
            {
                for(int c =0; c<in_image.chanels(); c++)
                {
                    image_src.at<cv::Vec4d>(row_i,col_i)[c] = in_image.Get(row_i,col_i,c);
                }

            }
            else if(in_image.chanels()==1)
            {
                image_src.at<double>(row_i,col_i) = in_image.Get(row_i,col_i,0);
            }


        }
    }
    cv::Mat rgb_image;
    image_src.convertTo(rgb_image,CV_8UC(in_image.chanels()));
    return rgb_image;
}

crazy::ImageMatrix convert_CVImage2ImageMatrix(cv::Mat in_image)
{
    cv::Mat rgb_image;
    in_image.convertTo(rgb_image,CV_64FC(in_image.channels()));
    crazy::ImageMatrix image_mat(rgb_image.rows,rgb_image.cols,rgb_image.channels(),0);
    for(int row_i=0; row_i<image_mat.rows(); row_i++)
    {
        for(int col_i=0; col_i<image_mat.cols(); col_i++)
        {

            if(image_mat.chanels()==3)
            {
                for(int c =0; c<image_mat.chanels(); c++)
                {
                    image_mat.Set(row_i,col_i,c,rgb_image.at<cv::Vec3d>(row_i,col_i)[c]);
                }

            }
            else if(image_mat.chanels()==4)
            {
                for(int c =0; c<image_mat.chanels(); c++)
                {
                    image_mat.Set(row_i,col_i,c,rgb_image.at<cv::Vec4d>(row_i,col_i)[c]);
                }

            }
            else if(image_mat.chanels()==1)
            {
                image_mat.Set(row_i,col_i,0,rgb_image.at<double>(row_i,col_i));
            }


        }
    }

    return image_mat;
}

crazy::DMatrix CvtCVMat2DMatrix(cv::Mat mat)
{
    mat.convertTo(mat,CV_64FC1);

    crazy::DMatrix d_matrix(mat.rows,mat.cols,0);
    for(int y=0; y<d_matrix.rows(); y++)
    {
        for(int x=0; x<d_matrix.cols(); x++)
        {
            d_matrix.Set(x,y,mat.at<double>(y,x));

        }
    }
    return  d_matrix;

}
cv::Mat CvtDMatrix2CVMat(crazy::DMatrix mat)
{
    cv::Mat CV_Mat(mat.rows(),mat.cols(),CV_64FC1);
    for(int row_i=0; row_i<mat.rows(); row_i++)
    {
        for(int col_i=0; col_i<mat.cols(); col_i++)
        {

            CV_Mat.at<double>(row_i,col_i) = mat.Get(row_i,col_i);

        }
    }
    return  CV_Mat.clone();

}


crazy::DMatrix CvtEigenTriplets2DMatrix(ArrayTriplet triplet)
{
    DMatrix dmat(triplet.GetSize(),3);
    for (int r = 0; r < triplet.size(); r++)
    {
        double j = triplet[r].row();
        double i = triplet[r].col();
        double value = triplet[r].value();

        dmat.Set(0,r,i);
        dmat.Set(1,r,j);
        dmat.Set(2,r,value);
    }
    return dmat;
}
ArrayTriplet CvtDMatrix2EigenTriplets(crazy::DMatrix DMat)
{

    ArrayTriplet triplet;
    for(int i=0; i<DMat.rows(); i++)
    {
        int x = DMat.Get(0,i);
        int y = DMat.Get(1,i);
        double value = DMat.Get(2,i);

        triplet.push_back(Eigen::Triplet<double>(y, x, value));

    }
    return triplet;

}



}

