#include <iostream>
#include <chrono>

#include "XMath/Algebra/Vector.h"

using namespace std;
using namespace xyh;

int main() 
{
	auto start = std::chrono::high_resolution_clock::now();
    cout << "--------test begins-----------" << endl;
    cout << "size of vec3: " << sizeof(vec3) << endl;
	vec3 v(1, 2, 3);
	vec3 u{ 0,2,3 };
	vec2 w(1.f);
    vec2 z(4.f , 2.f);
    cout << "v: " << v << endl;
	cout << "u: " << u << endl;
    cout << "w: " << w << endl;
    cout << "z: " << z << endl;

	cout << "--------test unary operator----"<< endl;
	cout << "-v: " << -v << endl;
    cout << "+u: " << +u << endl;

    cout << "--------test + - * /-----------" << endl;
	cout << "v + u: " << v + u << endl;
	cout << "v - u: " << v - u << endl;
	cout << "v += u: " << (v += u) << endl;
    v = vec3(1, 2, 3);
	cout << "v -= u: " << (v -= u) << endl;
    v = vec3(1, 2, 3);
	cout << "v * 5.f: " << v * 5.f << endl;
    cout << "v *= 5.f: " << (v *= 5.f) << endl;
    v = vec3(1, 2, 3);
	cout << "u / 0.5f: " << u / 0.5f << endl;
    cout << "u /= 5.f: " << (u /= 5.f) << endl;
	u *= 5.f;

	cout << "---------test inner product-----" << endl;
	cout << "dot(v, u): " << dot(v, u) << endl;
	cout << "dot(w, z): " << dot(w, z) << endl;
	
	cout << "---------test norm and normalize-----" << endl;
	cout << "norm(v): " << norm(v) << endl;
    cout << "sqrnorm(u): " << sqrnorm(u) << endl;
	cout << "normalize(v): " << normalize(v) << endl;
	v = vec3(1, 2, 3);

	// // angle
	// cout << vecf3::cos_theta(v, u) << endl;
	// cout << v.cos_theta(u) << endl;

	// // cross
	// cout << vecf3::cross(v, u) << endl;
	// cout << v.cross(u) << endl;

	// // cast
	// cout << v.cast_to<valf3>() << endl;

	// // lerp
	// cout << vecf3::lerp(v, u, 0.5) << endl;
	// cout << v.lerp(u, 0.5f) << endl;

	// // veci
	// veci3 iv{ 1,2,3 };
	// cout << iv * 5 << endl;
	// cout << iv * 7 << endl;

	// // project, perpendicular
	// cout << v.project(u.normalize()) << endl;
	// cout << v.perpendicular(u.normalize()) << endl;

	auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "time: " << duration.count() << std::endl;

}