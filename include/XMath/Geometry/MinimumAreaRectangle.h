#pragma once

#include <vector>
#include <numeric>

#include "QuickHull2D.h"
#include "../Algebra/Matrix.h"

namespace xyh{

// The class is a functor to support computing the minimum area box
// of a set of points
// see https://www.geometrictools.com/Documentation/MinimumAreaRectangle.pdf
template<typename Real> class MinimumAreaRectangle {
public:
    using Point = Point2<Real>;
    using Vector = Vector2<Real>;

    void run(size_t size, const Point* points, Real Eps = defaultEps<Real>());
    // call these function after calling run()
    Real area() {return result_.area; }
    const Matrix2<Real>& rotation_matrix() const {return result_.rotation; }
    const Vector& scale() {return result_.scale; }
    const Vector& translation() {return result_.translation;}
    const std::array<Point, 4>& extreme_point() {return result_.extreme;}

// Members and functions used for computing
private:
    void init_rec();
    void update_rec();
private:
    struct Rectangle {
        Real area;
        // the affine transform transforming a unit square to the oriented rectangle
        Matrix2<Real> rotation;
        Vector scale;
        Vector translation;
        std::array<Point, 4> extreme;
    };
    Rectangle result_;
    Rectangle itr_rec_;
    Real Epsilon_;
    std::array<size_t, 4> support;
    std::vector<const Point*> ch_;
    size_t ch_size_;
    std::vector<bool> visited_;
};

}
#include "details/MinimumAreaRectangle.inl"
