
#include "CMatrix.hpp"
namespace crazy
{
IMatrix::IMatrix(int r,int c):BaseMatrix(r,c)
{

}
IMatrix::IMatrix(int r,int c,int v):BaseMatrix(r,c,v)
{

}
IMatrix::~IMatrix()
{


}
bool IMatrix::Create(int r,int c)
{
    this->Base_Create(r,c);
    return true;
}
bool IMatrix::Create(int r,int c,int v)
{
    this->Base_Create(r,c);
    this->Base_Init(v);
    return true;
}
bool IMatrix::Set(int r,int c,int v)
{
    return this->Base_Set(r,c,v);
}
int IMatrix::Get(int r,int c)
{
    return  this->Base_Get(r,c);
}


FMatrix::FMatrix(int r,int c):BaseMatrix(r,c)
{


}

FMatrix::FMatrix(int r,int c, float v):BaseMatrix(r,c,v)
{

}
bool FMatrix::Create(int r,int c)
{
    this->Base_Create(r,c);
    return true;
}
bool FMatrix::Create(int r,int c,int v)
{
    this->Base_Create(r,c);
    this->Base_Init(v);
    return true;
}
FMatrix::~FMatrix()
{

}

bool FMatrix::Set(int r,int c,float v)
{
    return this->Base_Set(r,c,v);


}
float FMatrix::Get(int r,int c)
{
    return  this->Base_Get(r,c);

}


DMatrix::DMatrix(int r,int c):BaseMatrix(r,c)
{

}
DMatrix::DMatrix(int r,int c,double v):BaseMatrix(r,c,v)
{
}
DMatrix::~DMatrix()
{

}
bool DMatrix::Create(int r,int c)
{
    this->Base_Create(r,c);
    return true;
}
bool DMatrix::Create(int r,int c,int v)
{
    this->Base_Create(r,c);
    this->Base_Init(v);
    return true;
}
bool DMatrix::Set(int r,int c,double v)
{
    return this->Base_Set(r,c,v);
}
double DMatrix::Get(int r,int c)
{
    return  this->Base_Get(r,c);

}


ImageMatrix::ImageMatrix(int r,int c,int channels_n)
{
    this->Create(r,c,channels_n);
}
ImageMatrix::ImageMatrix(int r,int c,int channels_n,double v)
{
    this->Create(r,c,channels_n,v);

}
ImageMatrix::~ImageMatrix()
{

    images.clear();
}
bool ImageMatrix::Create(int r,int c,int channels_n)
{

    for(int i=0; i<channels_n; i++)
    {
        images.Add(DMatrix(r,c));

    }
}
bool ImageMatrix::Create(int r,int c,int channels_n,double v)
{
    for(int i=0; i<channels_n; i++)
    {
        images.Add(DMatrix(r,c,v));


    }
}

bool ImageMatrix::Set(int r,int c,int channels_n,double v)
{
    return images.Get(channels_n).Set(r,c,v);
}
double ImageMatrix::Get(int r,int c,int channels_n)
{
    return images.Get(channels_n).Get(r,c);
}


}
