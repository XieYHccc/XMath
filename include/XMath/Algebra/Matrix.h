#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <initializer_list>

#include "../Utils/Array2D.h"
#include "Vector.h"

namespace xyh
{
// Real based Matrix
template<typename Real, size_t NumRows, size_t NumCols>
class Matrix : public Array2D<Real, NumRows, NumCols>
{
public:
    using Array2D<Real, NumRows, NumCols>::Array2D;
    using Array2D<Real, NumRows, NumCols>::operator();

    // construct a 3x3 Matrx from vectors
    Matrix(const Vector<Real, 3>& v0, const Vector<Real, 3>& v1, const Vector<Real, 3>& v2)
    {
        set_col(0, v0);
        set_col(1, v1);
        set_col(2, v2);
    }

    void set_row(size_t row, const Vector<Real, NumCols>& v)
    {
        assert(row < NumRows);
        for(size_t col = 0; col < NumCols; ++col)
            operator()(row, col) = v[col];
    }

    void set_col(size_t col, const Vector<Real, NumRows>& v)
    {
        assert(col < NumCols);
        for (size_t row = 0; row < NumRows; ++row)
            operator()(row, col) = v[row];
    }

    Vector<Real, NumCols> get_row(size_t row) const
    {
        assert(row < NumRows);
        Vector<Real, NumCols> result;
        for (size_t col = 0; col < NumCols; ++col)
            result[col] = operator()(row, col);
        return result;
    }

    Vector<Real, NumRows> get_col(size_t col) const
    {
        assert(col < NumCols);
        Vector<Real, NumRows> result;
        for (size_t row = 0; row < NumRows; ++row)
            result[row] = operator()(row, col);
        return result;
    }

    static Matrix<Real, NumRows, NumCols> Zero()
    {
        return Matrix<Real, NumRows, NumCols>{};
    }

    static Matrix<Real, NumRows, NumCols> Identity()
    {
        Matrix<Real, NumRows, NumCols> result{};
        constexpr size_t numDiagonal = std::min(NumRows, NumCols);
        for(size_t i = 0; i < numDiagonal; ++i)
            result(i, i) = (Real)1;
        return result;
    }


};

// type alias
template<typename Real>
using Matrix3 = Matrix<Real, 3, 3>;
using mat3 = Matrix3<float>;
using mat3d = Matrix3<double>;
using mat3i = Matrix3<int>;

// ==================================Unary operations====================================
template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols> operator+(const Matrix<Real, NumRows, NumCols>& m)
{
    return m;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols> operator-(const Matrix<Real, NumRows, NumCols>& m)
{
    Matrix<Real, NumRows, NumCols> result;
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        result[i] = -m[i];
    return result;
}
// ==================================linear operations====================================
template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols> operator+(const Matrix<Real, NumRows, NumCols>& m0,
const Matrix<Real, NumRows, NumCols>& m1)
{
    Matrix<Real, NumRows, NumCols> result = m0;
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        result[i] += m1[i];
    return result;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols>& operator+=(Matrix<Real, NumRows, NumCols>& m0,
const Matrix<Real, NumRows, NumCols>& m1)
{
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        m0[i] += m1[i];
    return m0;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols> operator-(const Matrix<Real, NumRows, NumCols>& m0,
const Matrix<Real, NumRows, NumCols>& m1)
{
    Matrix<Real, NumRows, NumCols> result = m0;
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        result[i] -= m1[i];
    return result;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols>& operator-=(Matrix<Real, NumRows, NumCols>& m0,
const Matrix<Real, NumRows, NumCols>& m1)
{
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        m0[i] -= m1[i];
    return m0;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols> operator*(const Matrix<Real, NumRows, NumCols>& m, const Real& r)
{
    Matrix<Real, NumRows, NumCols> result = m;
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        result[i] *= r;
    return result;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols> operator*(const Real& r, const Matrix<Real, NumRows, NumCols>& m)
{
    Matrix<Real, NumRows, NumCols> result = m;
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        result[i] *= r;
    return result;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols>& operator*=(Matrix<Real, NumRows, NumCols>& m, const Real& r)
{
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        m[i] *= r;
    return m;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols> operator/(const Matrix<Real, NumRows, NumCols>& m, const Real& r)
{
    assert(r != (Real)0);
    Matrix<Real, NumRows, NumCols> result = m;
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        result[i] /= r;
    return result;
}

template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols>& operator/=(Matrix<Real, NumRows, NumCols>& m, const Real& r)
{
    assert(r != (Real)0);
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        m[i] /= r;
    return m;
}
// ===============================linear operations finish=================================

// Compute the L2 Norm of a Matrix
template<typename Real, size_t NumRows, size_t NumCols>
Real norm_l2(const Matrix<Real, NumRows, NumCols>& m)
{
    Real result = 0;
    for(size_t i = 0; i < NumRows * NumCols; ++i)
        result += m[i] * m[i];
    return std::sqrt(result);
}

// Get the transose of a Matrix
template<typename Real, size_t NumRows, size_t NumCols>
Matrix<Real, NumRows, NumCols> transpose(const Matrix<Real, NumRows, NumCols>& m )
{
    Matrix<Real, NumRows, NumCols> result;
    for (size_t row = 0; row < NumRows; ++row)
    {
        for (size_t col = 0; col < NumCols; ++col)
            result(col, row) = m(row, col);
    }
    return result;
}

// =======================Matrix-Vector and Matrix-Matrix multiplication=========================

// M * v
template<typename Real, size_t NumRows, size_t NumCols>
Vector<Real, NumRows> operator*(const Matrix<Real, NumRows, NumCols>& m,
const Vector<Real, NumCols>& v)
{
    Vector<Real, NumRows> result{};
    for (size_t row = 0; row < NumRows; ++row)
    {
        for(size_t i = 0; i < NumCols; ++i)
            result[row] += m(row, i) * v[i];
    }
    return result;
}

// M0 * M1
template<typename Real, size_t NumRows, size_t NumCols, size_t NumCommon>
Matrix<Real, NumRows, NumCols> operator*(const Matrix<Real, NumRows, NumCommon>& m0,
const Matrix<Real, NumCommon, NumCols>& m1)
{
    Matrix<Real, NumRows, NumCols> result{};
    for (size_t row = 0; row < NumRows; ++row)
    {
        for (size_t col = 0; col < NumCols; ++col)
        {
            for (size_t i = 0; i < NumCommon; ++i)
                result(row, col) += m0(row, i) * m1(i, col);
        }
    }
    return result;
}

// ============================Additional support for Matrix3===============================

}