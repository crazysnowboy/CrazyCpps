#ifndef OPENPOSE_CORE_CPoint3D_HPP
#define OPENPOSE_CORE_CPoint3D_HPP
#include <iostream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "utilities/CrazyLog.hpp"
namespace crazy
{
template<typename T>
class CPoint3D
{
public:

    CPoint3D(const T x = 0, const T y = 0, const T z = 0);

    /**
     * Copy constructor.
     * It performs `fast copy`: For performance purpose, copying a CPoint3D<T> or CPoint3D<T> or cv::Mat just copies the reference, it still shares the same internal data.
     * Modifying the copied element will modify the original one.
     * Use clone() for a slower but real copy, similarly to cv::Mat and CPoint3D<T>.
     * @param CPoint3D CPoint3D to be copied.
     */
    CPoint3D<T>(const CPoint3D<T>& P);

    /**
     * Copy assignment.
     * Similar to CPoint3D<T>(const CPoint3D<T>& CPoint3D).
     * @param CPoint3D CPoint3D to be copied.
     * @return The resulting CPoint3D.
     */
    CPoint3D<T>& operator=(const CPoint3D<T>& P);

    /**
     * Move constructor.
     * It destroys the original CPoint3D to be moved.
     * @param CPoint3D CPoint3D to be moved.
     */
    CPoint3D<T>(CPoint3D<T>&& P);

    /**
     * Move assignment.
     * Similar to CPoint3D<T>(CPoint3D<T>&& CPoint3D).
     * @param CPoint3D CPoint3D to be moved.
     * @return The resulting CPoint3D.
     */
    CPoint3D<T>& operator=(CPoint3D<T>&& P);




    /**
     * Equal comparison operator.
     * @param CPoint3D CPoint3D<T> to be compared.
     * @result Whether the instance satisfies the condition with respect to CPoint3D.
     */
    inline bool operator==(const CPoint3D<T>& P) const
    {
        return (x == P.x )&&(y == P.y )&&(z == P.z );
    }

    /**
     * Not equal comparison operator.
     * @param CPoint3D CPoint3D<T> to be compared.
     * @result Whether the instance satisfies the condition with respect to CPoint3D.
     */
    inline bool operator!=(const CPoint3D<T>& P) const
    {
        return (x != P.x )||(y != P.y )||(z != P.z );
    }


    T &Mutable_X()
    {
        return x;
    }
    T &Mutable_Y()
    {
        return y;
    }
    T &Mutable_Z()
    {
        return z;
    }
    bool SetX(T x_in)
    {
        x=x_in;
    }
    bool SetY(T y_in)
    {
        y=y_in;
    }
    bool SetZ(T z_in)
    {
        z=z_in;
    }
    const T GetCX()
    {
        return x;
    }
    const T GetCY()
    {
        return y;
    }
    const T GetCZ()
    {
        return z;
    }
    cv::Vec3f to_vec3f()
    {
        cv::Vec3f vector(x,y,z);
        return  vector;

    }
    const T Get(int idx)
    {
        switch (idx)
        {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        default:
            std::cout <<"no such case"<<std::endl;
        }

    }


    // -------------------------------------------------- Basic Operators -------------------------------------------------- //
    CPoint3D<T>& operator+=(const CPoint3D<T>& P);

    CPoint3D<T> operator+(const CPoint3D<T>& P) const;

    CPoint3D<T>& operator+=(const T value);

    CPoint3D<T> operator+(const T value) const;

    CPoint3D<T>& operator-=(const CPoint3D<T>& P);

    CPoint3D<T> operator-(const CPoint3D<T>& P) const;

    CPoint3D<T>& operator-=(const T value);

    CPoint3D<T> operator-(const T value) const;

    CPoint3D<T>& operator*=(const T value);

    CPoint3D<T> operator*(const T value) const;

    CPoint3D<T>& operator/=(const T value);

    CPoint3D<T> operator/(const T value) const;


//private:
//    T x;
//    T y;
//    T z;
public:
    T x;
    T y;
    T z;
};



template<typename T>
CPoint3D<T>:: CPoint3D(const T x_, const T y_,const T z_) :
    x{x_},
    y{y_},
    z{z_}
{
}

template<typename T>
CPoint3D<T>::CPoint3D(const CPoint3D<T>& P)
{
    try
    {
        x = P.x;
        y = P.y;
        z = P.z;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
    }
}

template<typename T>
CPoint3D<T>& CPoint3D<T>::operator=(const CPoint3D<T>& P)
{
    try
    {
        x = P.x;
        y = P.y;
        z = P.z;
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
CPoint3D<T>::CPoint3D(CPoint3D<T>&& P)
{
    try
    {
        x = P.x;
        y = P.y;
        z = P.z;
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
    }
}

template<typename T>
CPoint3D<T>& CPoint3D<T>::operator=(CPoint3D<T>&& P)
{
    try
    {
        x = P.x;
        y = P.y;
        z = P.z;
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
CPoint3D<T>& CPoint3D<T>::operator+=(const CPoint3D<T>& P)
{
    try
    {
        x += P.x;
        y += P.y;
        z += P.z;
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
CPoint3D<T> CPoint3D<T>::operator+(const CPoint3D<T>& P) const
{
    try
    {
        return CPoint3D<T> {T(x + P.x), T(y + P.y),T(z + P.z)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint3D<T> {};
    }
}

template<typename T>
CPoint3D<T>& CPoint3D<T>::operator+=(const T value)
{
    try
    {
        x += value;
        y += value;
        z += value;
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
CPoint3D<T> CPoint3D<T>::operator+(const T value) const
{
    try
    {
        return CPoint3D<T> {T(x + value), T(y + value),T(z + value)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint3D<T> {};
    }
}

template<typename T>
CPoint3D<T>& CPoint3D<T>::operator-=(const CPoint3D<T>& P)
{
    try
    {
        x -= P.x;
        y -= P.y;
        z -= P.z;
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
CPoint3D<T> CPoint3D<T>::operator-(const CPoint3D<T>& P) const
{
    try
    {
        return CPoint3D<T> {T(x - P.x), T(y - P.y),T(z - P.z)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint3D<T> {};
    }
}

template<typename T>
CPoint3D<T>& CPoint3D<T>::operator-=(const T value)
{
    try
    {
        x -= value;
        y -= value;
        z -= value;
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
CPoint3D<T> CPoint3D<T>::operator-(const T value) const
{
    try
    {
        return CPoint3D<T> {T(x - value), T(y - value),T(z - value)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint3D<T> {};
    }
}

template<typename T>
CPoint3D<T>& CPoint3D<T>::operator*=(const T value)
{
    try
    {
        x *= value;
        y *= value;
        z *= value;
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
CPoint3D<T> CPoint3D<T>::operator*(const T value) const
{
    try
    {
        return CPoint3D<T> {T(x * value), T(y * value),T(z * value)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint3D<T> {};
    }
}

template<typename T>
CPoint3D<T>& CPoint3D<T>::operator/=(const T value)
{
    try
    {
        x /= value;
        y /= value;
        z /= value;
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
CPoint3D<T> CPoint3D<T>::operator/(const T value) const
{
    try
    {
        return CPoint3D<T> {T(x / value), T(y / value),T(z / value)};
    }
    catch (const std::exception& e)
    {
        error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        return CPoint3D<T> {};
    }
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, CPoint3D<T>& P)
{
    os <<"["<< P.GetCX()<<" "<<P.GetCY()<<" "<<P.GetCZ()<<"]";
    return os;
}
}

#endif // OPENPOSE_CORE_CPoint3D_HPP
