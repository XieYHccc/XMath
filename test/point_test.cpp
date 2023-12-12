#include <iostream>

#include "XMath/Algebra/Point.h"

using namespace std;
using namespace xyh;

int main()
{  
    cout <<"==============================" << endl;
    cout <<"         test begins          " << endl;
    cout <<"==============================" << endl;
    point3 p0(1, 2, 3);
    point3 p1{2, 4, 5};
    vec3 v0(1, 1, 1);
    cout << "p0: " << p0 << endl;
    cout << "p1: " << p1 << endl;
    cout << "v0: " << v0 << endl;
    
    cout <<"==============================" << endl;
    cout <<"    test unary operations    " << endl;
    cout <<"==============================" << endl;
    cout << "+p1: " << +p1 << endl;
    cout << "-p1: " << -p1 << endl;

    cout <<"==============================" << endl;
    cout <<" test affine space operations " << endl;
    cout <<"==============================" << endl;
    cout << "p0 + v0: " << p0 + v0 << endl;
    cout << "p0 += v0: " << (p0 += v0) << endl;
    p0 = point3(1, 2, 3);
    cout << "p0 - p1: " << p0 - p1 << endl;

}