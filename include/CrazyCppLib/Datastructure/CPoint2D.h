#ifndef OPENPOSE_CORE_CPoint2D_HPP
#define OPENPOSE_CORE_CPoint2D_HPP

#include <string>
#include "utilities/CrazyLog.hpp"
namespace crazy
{
template<typename T>
class CPoint2D
{
public:

    CPoint2D(const T x = 0, const T y = 0);

    CPoint2D<T>(const CPoint2D<T>& P);

    CPoint2D<T>& operator=(const CPoint2D<T>& P);


    CPoint2D<T>(CPoint2D<T>&& P);


    CPoint2D<T>& operator=(CPoint2D<T>&& P);




    inline bool operator==(const CPoint2D<T>& P) const
    {
        return (x == P.x )&&(y == P.y );
    }


    inline bool operator!=(const CPoint2D<T>& P) const
    {
        return (x != P.x )||(y != P.y );
    }


    T &Mutable_X()
    {
        return x;
    }
    T &Mutable_Y()
    {
        return y;
    }

    const T GetCX()
    {
        return x;
    }
    const T GetCY()
    {
        return y;
    }

    bool SetX(T x_)
    {
        x=x_;
        return  true;
    }
    bool SetY(T y_)
    {
        y=y_;
        return  true;
    }


    // -------------------------------------------------- Basic Operators -------------------------------------------------- //
    CPoint2D<T>& operator+=(const CPoint2D<T>& P);

    CPoint2D<T> operator+(const CPoint2D<T>& P) const;

    CPoint2D<T>& operator+=(const T value);

    CPoint2D<T> operator+(const T value) const;

    CPoint2D<T>& operator-=(const CPoint2D<T>& P);

    CPoint2D<T> operator-(const CPoint2D<T>& P) const;

    CPoint2D<T>& operator-=(const T value);

    CPoint2D<T> operator-(const T value) const;

    CPoint2D<T>& operator*=(const T value);

    CPoint2D<T> operator*(const T value) const;

    CPoint2D<T>& operator/=(const T value);

    CPoint2D<T> operator/(const T value) const;

//private:
//    T x;
//    T y;


public:
    T x;
    T y;

};


template<typename T>
CPoint2D<T>::CPoint2D(const T x_, const T y_) :
    x{x_},
    y{y_}
{
}

template<typename T>
CPoint2D<T>::CPoint2D(const CPoint2D<T>& CPoint2D)
{
    try
    {
        x = CPoint2D.x;
        y = CPoint2D.y;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
    }
}

template<typename T>
CPoint2D<T>& CPoint2D<T>::operator=(const CPoint2D<T>& p)
{
    try
    {
        x = p.x;
        y = p.y;
        // Return
        return *this;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return *this;
    }
}

template<typename T>
CPoint2D<T>::CPoint2D(CPoint2D<T>&& p)
{
    try
    {
        x = p.x;
        y = p.y;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
    }
}

template<typename T>
CPoint2D<T>& CPoint2D<T>::operator=(CPoint2D<T>&& P)
{
    try
    {
        x = P.x;
        y = P.y;
        // Return
        return *this;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return *this;
    }
}


template<typename T>
CPoint2D<T>& CPoint2D<T>::operator+=(const CPoint2D<T>& P)
{
    try
    {
        x += P.x;
        y += P.y;
        // Return
        return *this;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return *this;
    }
}

template<typename T>
CPoint2D<T> CPoint2D<T>::operator+(const CPoint2D<T>& P) const
{
    try
    {
        return CPoint2D<T> {T(x + P.x), T(y + P.y)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint2D<T> {};
    }
}

template<typename T>
CPoint2D<T>& CPoint2D<T>::operator+=(const T value)
{
    try
    {
        x += value;
        y += value;
        // Return
        return *this;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return *this;
    }
}

template<typename T>
CPoint2D<T> CPoint2D<T>::operator+(const T value) const
{
    try
    {
        return CPoint2D<T> {T(x + value), T(y + value)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint2D<T> {};
    }
}

template<typename T>
CPoint2D<T>& CPoint2D<T>::operator-=(const CPoint2D<T>& P)
{
    try
    {
        x -= P.x;
        y -= P.y;
        // Return
        return *this;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return *this;
    }
}

template<typename T>
CPoint2D<T> CPoint2D<T>::operator-(const CPoint2D<T>& P) const
{
    try
    {
        return CPoint2D<T> {T(x - P.x), T(y - P.y)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint2D<T> {};
    }
}

template<typename T>
CPoint2D<T>& CPoint2D<T>::operator-=(const T value)
{
    try
    {
        x -= value;
        y -= value;
        // Return
        return *this;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return *this;
    }
}

template<typename T>
CPoint2D<T> CPoint2D<T>::operator-(const T value) const
{
    try
    {
        return CPoint2D<T> {T(x - value), T(y - value)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint2D<T> {};
    }
}

template<typename T>
CPoint2D<T>& CPoint2D<T>::operator*=(const T value)
{
    try
    {
        x *= value;
        y *= value;
        // Return
        return *this;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return *this;
    }
}

template<typename T>
CPoint2D<T> CPoint2D<T>::operator*(const T value) const
{
    try
    {
        return CPoint2D<T> {T(x * value), T(y * value)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint2D<T> {};
    }
}

template<typename T>
CPoint2D<T>& CPoint2D<T>::operator/=(const T value)
{
    try
    {
        x /= value;
        y /= value;
        // Return
        return *this;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return *this;
    }
}

template<typename T>
CPoint2D<T> CPoint2D<T>::operator/(const T value) const
{
    try
    {
        return CPoint2D<T> {T(x / value), T(y / value)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint2D<T> {};
    }
}
}

#endif // OPENPOSE_CORE_CPoint2D_HPP
