
#ifndef CRAZY_ARRAY_H

#include <CrazyLog.hpp>
#include <vector>

namespace crazy
{

template <typename ElementType>
class CArray:public std::vector<ElementType>
{
public:
    CArray()
    {

    }
    CArray(int n,ElementType initial_data)
    {
        this->Resize(n,initial_data);

    }
    int  GetSize()
    {
        return this->size();
    }

    bool Resize(int size_n)
    {
        std::vector<ElementType>::resize(size_n);
        return true;
    }
    bool Resize(int size_n,ElementType e)
    {
        std::vector<ElementType>::resize(size_n);
        for(int j=0; j<size_n; j++)
        {
            this->Get(j) = e;
        }
        return true;
    }
    /**
     * index element
     * @param id
     * @return ElementType
     */
    ElementType &Get(int idx)
    {

        if(idx<GetSize())
        {
            return (*this)[idx];
        }
        else
        {
            error("idx > = GetSize",__LINE__,__FUNCTION__,__FILE__);
        }
    }

    bool Add(const ElementType data)
    {
        this->push_back(data);

        return true;
    }

    bool Remove(int idx)
    {
        this->erase(this->begin()+idx);

        return true;
    }

    bool clear()
    {
        std::vector<ElementType>::clear();
        return true;

    }

    void push_back(ElementType in)
    {

        std::vector<ElementType>::push_back(in);
    }


};



}

using namespace crazy;

#define CRAZY_ARRAY_H

#endif //CRAZY_ARRAY_H
