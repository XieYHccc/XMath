#pragma once

#include "Vector.h"

namespace xyh::XMath {

// Point defined in Affine Space
template <typename Real, size_t N> 
class Point : public Array1D<Real, N> {
public:
    using Array1D<Real, N>::Array1D;

    // return the corresponding vector in vector space
    Vector<Real, N>& to_vector() noexcept {
        return reinterpret_cast<Vector<Real, N>&>(*this);
    }
    const Vector<Real, N>& to_vector() const noexcept {
        return const_cast<Point<Real, N>*>(this)->to_vector();
    }
};

// type alias
template<typename Real>
using Point2 = Point<Real, 2>;
using point2 = Point2<float>;
using point2i = Point2<int>;
using point2d = Point2<double>;

template<typename Real>
using Point3 = Point<Real, 3>;
using point3 = Point3<float>;
using point3i = Point3<int>;
using point3d = Point3<double>;

// ==================================unary operations==================================
template<typename Real, size_t N>
inline Point<Real, N> operator+(const Point<Real, N>& p) {
    return p;
}

template<typename Real, size_t N>
inline Point<Real, N> operator-(const Point<Real, N>& p) {
    Point<Real, N> result;
    for (size_t i = 0; i < N; ++i)
        result[i] = -p[i];
    return result;
}

// =========================operations for point in Affine Space=========================
// point - point = vector 
template<typename Real, size_t N>
inline Vector<Real, N> operator-(const Point<Real, N>& p0, const Point<Real, N>&p1) {
    Vector<Real, N> result;
    for (size_t i = 0; i < N; ++i)
        result[i] = p0[i] - p1[i];
    return result;
}

// point + vector = point
template<typename Real, size_t N>
inline Point<Real, N> operator+(const Point<Real, N>& p, const Vector<Real, N>&v) {
    Point<Real, N> result;
    for (size_t i = 0; i < N; ++i)
        result[i] = p[i] + v[i];
    return result;
}

template<typename Real, size_t N>
inline Point<Real, N>& operator+=(Point<Real, N>& p, const Vector<Real, N>&v) {
    for (size_t i = 0; i < N; ++i)
        p[i] += v[i];
    return p;
}

template<typename Real, size_t N>
inline Point<Real, N> operator*(const Point<Real, N>& p, const Real& real) {
    Point<Real, N> result = p;
    for (size_t i = 0; i < N; ++i)
        result[i] *= real;
    return result;
}

template<typename Real, size_t N>
inline Point<Real, N> operator*(const Real& real, const Point<Real, N>& p) {
    Point<Real, N> result = p;
    for (size_t i = 0; i < N; ++i)
        result[i] *= real;
    return result;
}

template<typename Real, size_t N>
inline Point<Real, N>& operator*=(Point<Real, N>& p, const Real& real) {
    for (size_t i = 0; i < N; ++i)
        p[i] *= real;
    return p;
}

template<typename Real, size_t N>
inline Point<Real, N> operator/(const Point<Real, N>& p, const Real& real) {
    assert(real != 0);
    Point<Real, N> result = p;
    for (size_t i = 0; i < N; ++i)
        result[i] /= real;
    return result;
}

template<typename Real, size_t N>
inline Point<Real, N>& operator/=(Point<Real, N>& p, const Real& real) {
    assert(real != 0);
    for (size_t i = 0; i < N; ++i)
        p[i] /= real;
    return p;
}
}