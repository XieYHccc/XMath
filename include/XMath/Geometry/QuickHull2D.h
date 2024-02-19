#pragma once

#include <array>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>

#include "../Algebra/Point.h"
#include "../Algebra/Vector.h"
#include "../Constants.h"

namespace xyh::XMath {

template<typename Real> class QuickHull2D {
public:
    using Point = Point2<Real>;
    // run quickhull
    void runqhull(size_t size, const Point* points, bool ccw = false, Real Epsilon = defaultEps<Real>());

    const std::vector<const Point*>& get_hull_points() const {return hull_point_;}
    const std::vector<std::array<const Point*, 2>>& get_hull_lines() const {return hull_line_;}

private:
    void findsidehull(const Point** rhs, size_t size, const Point* P, const Point* Q);
    // sort convex hull points as counter-clock wise
    void sort();

private:
    Real Epsilon_;
    std::vector<const Point*> hull_point_;
    std::vector<std::array<const Point*, 2>> hull_line_;
};

}
#include "details/QuickHull2D.inl"