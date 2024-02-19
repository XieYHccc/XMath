// Affine Transformation is defined for points in affine space.
// However we could regrad it as the composition of a linear transformation(to self)
// and a translation in corresponding Vector Space.
// what't more, this composition can be represented as a linear transformation in N+1 dimension
// the correspoing matrix is called homogeneous matrix

#pragma once

#include "Matrix.h"

namespace xyh::XMath {
// In this class we decompose Affine Transformation into rotation, reflection, shearing
template<typename Real, size_t N>
class AffineTransform
{
public:

private:
    Matrix<Real, N + 1, N + 1> homo_matrix_;
    Matrix<Real, N, N> matrix_; // general / rotation matrix
    

};



}
