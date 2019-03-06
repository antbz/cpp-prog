#include <iostream>

using namespace std;

int main() {
    double a, b, c, d, e, f, x, y;

    cout << "EQ1: Input a, b and c (ax + by = c): ";
    cin >> a >> b >> c;
    cout << "EQ2: Input d, e and f (dx + ey = f): ";
    cin >> d >> e >> f;

    if ((a * e - b * d) != 0) {
        x = (c * e - b * f) / (a * e - b * d);
        y = (a * f - c * d) / (a * e - b * d);
        cout << "x = " << x << endl << "y = " << y;
    }
    else {
        if (c / b != f / e) {
            cout << "The system of equations is inconsistent";
        }
        else {
            cout << "The system of equations is consistent and dependent";
        }
    }

    return 0;
}