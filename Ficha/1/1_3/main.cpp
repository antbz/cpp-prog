#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const double pi = 3.14159265359;
    double M, p, r;

    cout << "Whats is the specific mass (p in Kg/m3)? ";
    cin >> p;
    cout << "What is the radius (r in m)? ";
    cin >> r;

    M = (4 / 3) * (p * pi * pow(r, 3));

    cout << "The sphere has mass " << M << " Kg";

    return 0;
}