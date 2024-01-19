#include <iostream>
#include <vector>
#include <random>

#include <XMath/Geometry/QuickHull2D.h>

using namespace xyh;

int main() {
    // 使用随机设备作为种子
    std::random_device rd;
    // 使用随机设备生成引擎
    std::mt19937 gen(rd());
    // 定义浮点数范围
    std::uniform_real_distribution<double> distribution(0.0, 10.0);
    
    std::vector<point2> points;
    for (size_t i = 0; i < 50; ++i) 
        points.emplace_back(distribution(gen), distribution(gen));
    QuickHull2D<float> qhull;
    qhull.runqhull(points.size(), points.data());
    
    // output the results
    auto& hull_points = qhull.get_hull_points();
    std::vector<point2> hull_array;
    for (auto p : hull_points)
        hull_array.push_back(*p);
}