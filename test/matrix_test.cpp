#include <iostream>
#include <chrono>

#include "XMath/Algebra/Matrix.h"
#include "XMath/Algebra/Vector.h"

using namespace std;
using namespace xyh;

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    cout <<"==============================" << endl;
    cout <<"         test begins          " << endl;
    cout <<"==============================" << endl;
    mat3 m0{};
    m0.fill(1.f);
    m0.set_row(1, vec3(2, 2, 2));
    m0.set_col(2, vec3(3, 2, 1));
    vec3 v0(1, 2, 3);
    vec3 v1(4, 5, 6);
    vec3 v2(7, 8, 9);
    mat3 m1{v0, v1, v2};
    mat3 m2{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    cout << "m0:" << endl << m0 ;
    cout << "m1:" << endl << m1 ;
    cout << "m2:" << endl << m2 ;
    cout << "v0: " << v0 << endl;

    cout <<"==============================" << endl;
    cout <<"    test unary operations    " << endl;
    cout <<"==============================" << endl;
    cout << "+m2:" << endl << +m2;
    cout << "-m2:" << endl << -m2;
    
    cout <<"==============================" << endl;
    cout <<"    test linear operations    " << endl;
    cout <<"==============================" << endl;
    cout << "m0 + m1:" << endl << m0 + m1;
    cout << "m0 - m1:" << endl << m0 - m1;
    cout << "m2 * 2.f:" << endl << m2 * 2.f;
    cout << "m2 / 2.f:" << endl << m2 / 2.f;
    cout << "m2 += m1:" << endl << (m2 += m1);
    m2.fill(1.f);
    cout << "m2 -= m1:" << endl << (m2 -= m1);
    m2.fill(1.f);
    cout << "m2 *= 2.f:" << endl << (m2 *= 2.f);
    m2.fill(1.f);
    cout << "m2 /= 2.f:" << endl << (m2 /= 2.f);
    m2.fill(1.f);

    cout <<"==============================" << endl;
    cout <<" test M-M M-V multiplication  " << endl;
    cout <<"==============================" << endl;
    cout << "m0 * m1:" << endl << m0 * m1;
    cout << "m1 * v0:" << endl << m1 * v0 << endl;

    cout <<"==============================" << endl;
    cout << "transpose(m1):" << endl << transpose(m1);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "time: " << duration.count() << std::endl;

}

