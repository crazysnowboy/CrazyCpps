
#ifndef CRAZY_BASEMATRIX_H
#include<string>
#include <CArray.hpp>
#include <shared_ptr.hpp>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>

#undef NDEBUG
#include<assert.h>
#define NDEBUG

namespace crazy
{

template <typename Dtype>
class MeteData
{
public:
    MeteData(long int data_size)
    {
        data = new Dtype[data_size];
    }
    ~MeteData()
    {
        delete(data);
    }

    Dtype &Get(int idx)
    {
        return data[idx];
    }
    bool Set(int idx,Dtype d)
    {
        data[idx] = d;
        return true;
    }

    Dtype *Data()
    {
        return data;
    }
private:

    Dtype *data;

};


template<typename ElementType>
class DArray
{
public:
    DArray()
    {

        this->clear();
    }
    DArray(int n,int initial_data)
    {

        this->resize(n,initial_data);

    }
    ~DArray()
    {
        this->clear();

    }
    int  GetSize()
    {
        if(data == nullptr)
        {
            data_size = 0;
        }

        return data_size;

    }

    bool resize(int size_n)
    {
        this->clear();
        data_size= size_n;
        data = std::make_shared<MeteData<ElementType>>(size_n);

        return true;
    }
    bool resize(int size_n,ElementType e)
    {
        this->resize(size_n);
        for(int j=0; j<size_n; j++)
        {
            this->Get(j) = e;
        }
        return true;
    }

    ElementType &Get(int idx)
    {

        if(idx<GetSize())
        {

            return data.get()->Get(idx);
        }
        else
        {
            error("idx > = GetSize or data == nullptr",__LINE__,__FUNCTION__,__FILE__);
        }
    }

    bool Set(int idx,ElementType d)
    {

        if(idx<GetSize())
        {

            data.get()->Set(idx,d);
            return true;
        }
        else
        {
            error("idx > = GetSize or data == nullptr",__LINE__,__FUNCTION__,__FILE__);
            return false;
        }
    }

    bool clear()
    {
        data_size=0;

        return true;

    }

    ElementType *Data()
    {
        return data.get()->Data();
    }


private:

    std::shared_ptr<MeteData<ElementType>> data;
    long int data_size =0;
};


template<typename Dtype>
class BaseMatrix
{
protected:

    BaseMatrix() {}

    BaseMatrix(int r,int c)
    {
        this->Base_Create(r,c);

    }
    BaseMatrix(int r,int c,Dtype v)
    {
        this->Base_Create(r,c);
        this->Base_Init(v);

    }
    ~BaseMatrix()
    {
        this->Base_Release();

    }
    bool Base_Create(int r,int c)
    {

        this->Base_Release();
        data.resize(r*c);

//        std::cout <<"r = "<<r<<"    c="<<c<<std::endl;
        rows_=r;
        cols_=c;
        return true;
    }
    bool Base_Init(Dtype init_value)
    {
        for(int y=0; y<rows(); y++)
        {
            for(int x=0; x<cols(); x++)
            {
                data.Get(y*cols() + x) = init_value;
            }
        }
    }

    bool Base_Release()
    {

        rows_=0;
        cols_=0;
        data.clear();

        return true;
    }

    bool Base_Set(int r,int c,Dtype v)
    {

        assert(c<cols());
        assert(r<rows());

        data.Get(r*cols() + c) =v;
        return true;

    }
    Dtype Base_Get(int r,int c)
    {
        assert(c<cols());
        assert(r<rows());
        return data.Get(r*cols() + c);
    }

public:
    int rows()
    {
        return rows_;
    }
    int cols()
    {
        return cols_;
    }
    Dtype * Data()
    {
        return data.Data();
    }
private:

    int rows_ = 0;
    int cols_ = 0;

//    CArray<Dtype> data;
    DArray<Dtype> data;


};
}
#define CRAZY_BASEMATRIX_H

#endif //CRAZY_ARRAY_H
