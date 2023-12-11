#pragma once

#include "Vector.h"

namespace xyh
{

// Point defined in Affine Space
template <typename Real, size_t N> 
class Point : public Array<Real, N>
{
public:
    using Array<Real, N>::Array;

    // return the corresponding vector in vector space
    Vector<Real, N>& to_vector() noexcept
    {
        return reinterpret_cast<Vector<Real, N>&>(*this);
    }
    
    const Vector<Real, N>& to_vector() const noexcept
    {
        return const_cast<Point<Real, N>*>(this)->to_vector();
    }
};

// type alias
template<typename Real>
using Point2 = Point<Real, 2>;
using point2 = Point2<float>;

template<typename Real>
using Point3 = Point<Real, 3>;
using point3 = Point3<float>;


// -------------------operations for point in Affine Space---------------------
// unary operators
template<typename Real, size_t N>
inline Point<Real, N> operator+(const Point<Real, N>& p)
{
    return p;
}

template<typename Real, size_t N>
inline Point<Real, N> operator-(const Point<Real, N>& p)
{
    Point<Real, N> result{};
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = -p[i];
    }
    return result;
}

// point - point = vector 
template<typename Real, size_t N>
inline Vector<Real, N> operator-(const Point<Real, N>& p0, const Point<Real, N>&p1)
{
    Vector<Real, N> result{};
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = p0[i] - p1[i];
    }
    return result;
    
}

// point + vector = point
template<typename Real, size_t N>
inline Vector<Real, N> operator+(const Point<Real, N>& p, const Vector<Real, N>&v)
{
    Point<Real, N> result{};
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = p[i] + v[i];
    }
    return result;
    
}
}