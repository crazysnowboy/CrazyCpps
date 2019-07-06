
#ifndef CRAZY_MATRIX_H
#include "BaseMatrix.hpp"
namespace crazy
{
class IMatrix:public BaseMatrix<int>
{
public:
    IMatrix() {};

    IMatrix(int r,int c);
    IMatrix(int r,int c,int v);
    ~IMatrix();
    bool Create(int r,int c);
    bool Create(int r,int c,int v);

    bool Set(int r,int c,int v);
    int Get(int r,int c);
};
class FMatrix:public BaseMatrix<float>
{
public:
    FMatrix() {};

    FMatrix(int r,int c);
    FMatrix(int r,int c,float v);
    ~FMatrix();
    bool Create(int r,int c);
    bool Create(int r,int c,int v);

    bool Set(int r,int c,float v);
    float Get(int r,int c);
};

class DMatrix:public BaseMatrix<double>
{
public:
    DMatrix() {};

    DMatrix(int r,int c);
    DMatrix(int r,int c,double v);
    ~DMatrix();

    bool Create(int r,int c);
    bool Create(int r,int c,int v);

    bool Set(int r,int c,double v);
    double Get(int r,int c);


};

class ImageMatrix
{
public:
    ImageMatrix() {};

    ImageMatrix(int r,int c,int channels_n);
    ImageMatrix(int r,int c,int channels_n,double v);

    ~ImageMatrix();

    bool Create(int r,int c,int channels_n);
    bool Create(int r,int c,int channels_n, double v);

    bool Set(int r,int c,int channels_n,double v);
    double Get(int r,int c,int channels_n);

    int rows()
    {
        return  images.Get(0).rows();
    }
    int cols()
    {
        return  images.Get(0).cols();
    }
    int chanels()
    {
        return  images.GetSize();
    }


private:

    CArray<DMatrix> images;

};


typedef CArray<Eigen::Triplet<double> > ArrayTriplet;


};
#define CRAZY_MATRIX_H

#endif //CRAZY_ARRAY_H
