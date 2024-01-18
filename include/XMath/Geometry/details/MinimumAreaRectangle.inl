#pragma once

namespace xyh {
    
template<typename Real>
void MinimumAreaRectangle<Real>::run(size_t size, const Point* points, Real Eps) {
    Epsilon_ = Eps;
    // -----------------------------1.Compute the convex hull-------------------------------
    QuickHull2D<float> qhull;
    qhull.runqhull(size, points, true);
    ch_ = qhull.get_hull_points();
    ch_size_ = ch_.size();
    visited_.resize(ch_.size(), false);
    visited_[0] = true;
    init_rec();
    update_rec();
}

template<typename Real>
void MinimumAreaRectangle<Real>::init_rec() {
    const Point& front = *ch_.front();
    const Point& end = *ch_.back();
    support[0] = 0;
    Vector init_dir = front - end;
    normalize(init_dir);
    Vector init_perp = perp(init_dir);
    itr_rec_.rotation.set_col(0, init_dir);
    itr_rec_.rotation.set_col(1, init_perp);
    // helpers to store the extremes, order as right, top, left
    std::array<Vector, 4> extreme{Vector{},
                                  Vector(std::numeric_limits<float>::lowest()),
                                  Vector(std::numeric_limits<float>::lowest()),
                                  Vector(std::numeric_limits<float>::max())}; 
    extreme[0][0] = dot(init_dir, front.to_vector());
    extreme[0][1] = dot(init_perp, front.to_vector());
    for (size_t i = 0; i < ch_size_; ++i) {
        const Point& p = *ch_[i];
        Real projonbottom = dot(init_dir, p.to_vector());
        Real projonperp = dot(init_perp, p.to_vector());
        // New right maximum or same but closer to top
        if (projonbottom > extreme[1][0] ||
           (abs(projonbottom - extreme[1][0]) < Epsilon_ && projonperp > extreme[1][1]))
        {
            extreme[1][0] = projonbottom;
            extreme[1][1] = projonperp;
            support[1] = i;
        }
        // New top maximum or same but closer to left
        if (projonperp > extreme[2][1] ||
           (abs(projonperp - extreme[2][1]) < Epsilon_ && projonbottom < extreme[2][0])) 
        {
            extreme[2][0] = projonbottom;
            extreme[2][1] = projonperp;
            support[2] = i;
        }
        // New left maximum or same but closer to bottom
        if (projonbottom < extreme[3][0] ||
           (abs(projonbottom - extreme[3][0]) < Epsilon_ && projonperp < extreme[3][1]))
        {
            extreme[3][0] = projonbottom;
            extreme[3][1] = projonperp;
            support[3] = i;
        }
    }
    itr_rec_.scale = Vector(extreme[1][0] - extreme[3][0], extreme[2][1] - extreme[0][1]);
    itr_rec_.area = itr_rec_.scale[0] * itr_rec_.scale[1];
    itr_rec_.extreme[0] = *ch_[support[0]] + (extreme[1][0] - extreme[0][0]) * init_dir ;
    itr_rec_.extreme[1] = itr_rec_.extreme[0] + itr_rec_.rotation.get_col(1) * itr_rec_.scale[1];
    itr_rec_.extreme[2] = itr_rec_.extreme[1] + itr_rec_.rotation.get_col(0) * (-itr_rec_.scale[0]);
    itr_rec_.extreme[3] = itr_rec_.extreme[0] + itr_rec_.rotation.get_col(0) * (-itr_rec_.scale[0]);
    result_ = itr_rec_;
}
template<typename Real>
void MinimumAreaRectangle<Real>::update_rec() {
    // ------------------------------4.Update the rectangle----------------------------------
    int num;
    for(size_t i = 0; i < ch_size_ - 1; ++i) {
        // Caculate the candidate angles, which are between 0 - 90
        num = 0;
        std::array<Real, 4> sqr_sintheta;
        for (size_t j = 0; j < 4; ++j) {
            // there are duplicate vertices
            if (support[j] == support[(j+1) % 4])
                sqr_sintheta[j] = 2;
            else {
                const Point& p = *ch_[support[j]];
                const Point& p_right = *ch_[(support[j] + 1) % ch_.size()];
                Vector dir = itr_rec_.rotation.get_col(j % 2);
                Vector v = p_right - p;
                Real d= dot(v, dir);
                Real sin = 1 - (d * d) / dot(v, v);
                sqr_sintheta[j] = sin;
                if (std::abs(d) > Epsilon_) ++num;
#ifndef NDEBUG
                if (dot(v, v) == 0) throw std::logic_error("Line degenerate to point");    
#endif
            }
        }
        // The polygon is a rectangle, so the search is over.
        if (num == 0) break;

        // Sort angles
        std::array<size_t, 4> sorted_angle{0, 1, 2, 3};
        std::stable_sort(sorted_angle.begin(), sorted_angle.end(),
            [&sqr_sintheta](size_t m, size_t n) { return sqr_sintheta[m] < sqr_sintheta[n];});

        // Replace the support vertices of edges which attaining minimum angle
        float min_angle = sqr_sintheta[sorted_angle[0]];
        for (size_t j = 0; j < 4; ++j) {
            if(abs(min_angle - sqr_sintheta[j]) < Epsilon_)
                support[j] = (support[j] + 1) % ch_size_;
        }

        // Cycle the support vertices to that the bottom support occurs first
        std::array<size_t, 4> next_support;
        size_t new_first = sorted_angle[0];
        for (size_t j = 0; j < 4; ++j)
            next_support[j]  = support[(j + new_first) % 4];
        support = next_support;
        
        // if support[0] is visited, the search is over.
        if (visited_[support[0]]) 
            return;
        else
            visited_[support[0]] = true;
        
        // Update box and result
        Vector dir = *ch_[support[0]] - *ch_[(support[0] - 1)];
        normalize(dir);
        Vector perpdir = perp(dir);
        Real length1 = dot((*ch_[support[1]] - *ch_[support[3]]), dir);
        Real length2 = dot((*ch_[support[2]] - *ch_[support[0]]), perpdir);
        Real area = length1 * length2;

        itr_rec_.area = area;
        itr_rec_.scale = Vector(length1, length2);
        itr_rec_.rotation.set_col(0, dir);
        itr_rec_.rotation.set_col(1, perpdir);
        itr_rec_.extreme[0] = *ch_[support[0]] + dir *
                            dot((*ch_[support[1]] - *ch_[support[0]]), dir);
        itr_rec_.extreme[1] = itr_rec_.extreme[0] + perpdir * length2;
        itr_rec_.extreme[2] = itr_rec_.extreme[1] + dir * (-length1);
        itr_rec_.extreme[3] = itr_rec_.extreme[0] + dir * (-length1);

        if(area < result_.area)
            result_ = itr_rec_;
    }

    // Calculate the translation of the final rectangle
    for(auto& p : result_.extreme) {
        result_.translation[0] += p[0];
        result_.translation[1] += p[1];
    }
    result_.translation /= 4.f;
}
}