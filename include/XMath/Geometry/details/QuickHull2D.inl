#pragma once

namespace xyh {

template<typename Real>
void QuickHull2D<Real>::runqhull(size_t size, const Point* points, bool ccw, Real Epsilon) {
    Epsilon_ = Epsilon;

    // 1.Find left and right most point
    const Point* A = &points[0];
    const Point* B = A;
    for (size_t i = 1; i < size; ++i) {
        const Point& p = points[i];
        // New left maximum or same but closer to top
        if (p[0] < A->at(0) - Epsilon_ ||
            (std::abs(p[0] - A->at(0)) < Epsilon_ && p[1] > A->at(1) + Epsilon_))
            A = &p;
        // New right maximum or same but closer to top
        if (p[0] > B->at(0) + Epsilon_ ||
            (std::abs(p[0] - B->at(0)) < Epsilon_ && p[1] > B->at(1) + Epsilon_))
            B = &p;
    }
    hull_point_.push_back(A);
    hull_point_.push_back(B);

    // 2.Divide point set into 2 group S1 and S2.
    // S1 is to the right side of AB, S2 is to the right side of BA
    std::vector<const Point*> S1, S2;
    Vector2<Real>AB = *B - *A;
    Vector2<Real> perpAB = perp(AB);
    // normalize(perpAB);
    float Aproj = dot(A->to_vector(), perpAB); 
    for (size_t i = 0; i < size; ++i) {
        const Point& p = points[i];
        if (&p == A || &p == B) continue;
        
        float proj = dot(p.to_vector(), perpAB);
        if (proj < Aproj - Epsilon_)
            S1.push_back(&p);
        else if (proj > Aproj + Epsilon_)
            S2.push_back(&p);
    }

    // 3.Recursively find convex hull
    findsidehull(S1.data(), S1.size(), A, B);
    findsidehull(S2.data(), S2.size(), B, A);

    if (ccw) sort();
}

template<typename Real>
void QuickHull2D<Real>::findsidehull(const Point** rhs, size_t size, const Point* P, const Point* Q) {
    if (size == 0) {
        hull_line_.push_back(std::array<const Point*, 2>{P, Q});
        return;
    }

    Vector2<Real> PQ = *Q - *P;
    Vector2<Real> perpPQ = -perp(PQ);
    // normalize(perpPQ);
    // find farthest point from PQ
    const Point* C = nullptr;
    float max_height = std::numeric_limits<float>::lowest();
    for (size_t i = 0; i < size; ++i) {
        const Point& p = *rhs[i];
        float height = dot(p.to_vector(), perpPQ);
        if (height > max_height + Epsilon_) {
            max_height = height;
            C = &p;
        }
    }
    hull_point_.push_back(C);

    // Three points P, Q, C partition the set into three subset S0, S1, S2
    // S0 are points inside triangle PQC, S1 are points to the right side of line PC
    // S2 are points to the right side of line CQ
    std::vector<const Point*> S1, S2;
    Vector2<Real> PC = *C - *P;
    Vector2<Real> CQ = *Q - *C;
    Vector2<Real> perpPC = -perp(PC);
    Vector2<Real> perpCQ = -perp(CQ);
    // normalize(perpPC); normalize(perpCQ);
    float Cproj1 = dot(C->to_vector(), perpPC);     // C project to perpPC
    float Cproj2 = dot(C->to_vector(), perpCQ);     // C project to perpCQ
    for (size_t i = 0; i < size; ++i) {
        const Point& p = *rhs[i];
        if (dot(p.to_vector(), perpPC) > Cproj1 + Epsilon_)
            S1.push_back(&p);
        else if (dot(p.to_vector(), perpCQ) > Cproj2 + Epsilon_)
            S2.push_back(&p);
    }
    
    findsidehull(S1.data(), S1.size(), P, C);
    findsidehull(S2.data(), S2.size(), C, Q);

}

template<typename Real>
void QuickHull2D<Real>::sort() {
    size_t size = hull_point_.size();
    Point centroid(0);
    for (const auto p : hull_point_) {
        centroid[0] += p->at(0);
        centroid[1] += p->at(1);
    }
    centroid /= float(size);

    
    // Calculate bearing angle from centroid
    std::vector<float> angles;
    angles.reserve(size);
    for(const auto p : hull_point_)
        angles.push_back(std::atan2(p->at(1) - centroid[1], p->at(0) - centroid[0]));

    // Sort
    std::vector<size_t> order(size);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&angles](size_t i, size_t j) {
              return angles[i] < angles[j];});
    std::vector<const Point*> ccw_points(size);
    for(size_t i = 0; i < size; ++i)
        ccw_points[i] = hull_point_[order[i]];
    hull_point_.swap(ccw_points);
}
}   