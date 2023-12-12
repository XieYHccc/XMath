#pragma once	

#include <cmath>

#include <cstddef>
#include <array>

#include "../Utils/Array1D.h"

namespace xyh
{
//! Real based vector in inner product space
template <typename Real, size_t N> 
class Vector : public Array1D<Real, N>
{
public :
    using Array1D<Real, N>::Array1D;
};

// type alias
template<typename Real>
using Vector2 = Vector<Real, 2>;
using vec2 = Vector2<float>;
using vec2i = Vector2<int>;
using vec2d = Vector2<double>;
template<typename Real>
using Vector3 = Vector<Real, 3>;
using vec3 = Vector3<float>;
using vec3i = Vector3<int>;
using vec3d = Vector3<double>;

// ==================================linear operations====================================
template <typename Real, size_t N>
inline Vector<Real, N> operator+(const Vector<Real, N>& v)
{
	return v;
}

template <typename Real, size_t N>
inline Vector<Real, N> operator-(const Vector<Real, N>& v)
{
	Vector<Real, N> result;
	for(size_t i = 0; i < N; ++i)
	{
		result[i] = -v[i];
	}
	return result;
}

template <typename Real, size_t N>
inline Vector<Real, N>& operator+=(Vector<Real, N>& v0, const Vector<Real, N>& v1)
{
	for (size_t i = 0; i < N; ++i)
		v0[i] += v1[i];
	return v0;
}

template <typename Real, size_t N>
inline Vector<Real, N> operator+(const Vector<Real, N>& v0, const Vector<Real, N>& v1)
{
	Vector<Real, N> result = v0;
	for (size_t i = 0; i < N; ++i)
		result[i] += v1[i];
	return result;
}

template <typename Real, size_t N>
inline Vector<Real, N>& operator-=(Vector<Real, N>& v0, const Vector<Real, N>& v1)
{
	for (size_t i = 0; i < N; ++i)
		v0[i] -= v1[i];
	return v0;
}

template <typename Real, size_t N>
inline Vector<Real, N> operator-(const Vector<Real, N>& v0, const Vector<Real, N>& v1)
{
	Vector<Real, N> result = v0;
	for (size_t i = 0; i < N; ++i)
		result[i] -= v1[i];
	return result;
}

template <typename Real, size_t N>
inline Vector<Real, N>& operator*=(Vector<Real, N>& v0, const Real& real)
{
	for (size_t i = 0; i < N; ++i)
		v0[i] *= real;
	return v0;
}

template <typename Real, size_t N>
inline Vector<Real, N> operator*(Vector<Real, N>& v0, const Real& real)
{
	Vector<Real, N> result = v0;
	for (size_t i = 0; i < N; ++i)
		result[i] *= real;
	return result;
}

template <typename Real, size_t N>
inline Vector<Real, N> operator*(const Real& real, Vector<Real, N>& v0)
{
	Vector<Real, N> result = v0;
	for (size_t i = 0; i < N; ++i)
		result[i] *= real;
	return result;
}

template <typename Real, size_t N>
inline Vector<Real, N>& operator/=(Vector<Real, N>& v0, const Real& real)
{
	assert(real != Real(0));
	for (size_t i = 0; i < N; ++i)
		v0[i] /= real;
	return v0;
}

template <typename Real, size_t N>
inline Vector<Real, N> operator/(Vector<Real, N>& v0, const Real& real)
{
	assert(real != Real(0));
	Vector<Real, N> result = v0;
	for (size_t i = 0; i < N; ++i)
		result[i] /= real;
	return result;
}
// ===============================linear operations finish=================================

// Compute the square of length of a vector
template<typename Real, size_t N>
inline Real sqrnorm(const Vector<Real, N>& v)
{
	Real s{0.0};
	for(size_t i = 0; i < v.size(); ++i)
		s += v[i] * v[i];
	return s;
}
// Compute the length of a vector
template<typename Real, size_t N>
inline Real norm(const Vector<Real, N>& v)
{
	return std::sqrt(sqrnorm(v));
}

// Normalize a vector to unit length
template<typename Real, size_t N>
inline Vector<Real, N>& normalize(Vector<Real, N>& v)
{
	Real n = norm(v);
	if(n > (Real)0)
		v /= n;
	else
		v.fill(Real(0));
	return v;
}

// Compute the inner product of two vectors
template<typename Real, size_t N>
inline Real dot(const Vector<Real, N>& v0, const Vector<Real, N>& v1)
{
	Real result = v0[0] * v1[0];
	for(size_t i = 1; i < N; ++i)
		result += v0[i] * v1[i];
	return result;
}

// ==============================Additional support for Vector2==============================
//! compute perpendicular vector (rotate vector counter-clockwise by 90 degrees)
template<typename Real>
inline Vector2<Real> perp(const Vector2<Real>& v)
{
    return Vector2<Real>(-v[1], v[0]);
}

// ==============================Additional support for Vector3==============================
template<typename Real>
inline Real dot(const Vector3<Real>& v0, const Vector3<Real>& v1)
{
	return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
}


}
