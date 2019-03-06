#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double x1, x2, x3, y1, y2, y3, a, b, c, s, area;

    cout << "Input point A (x1 y1): ";
    cin >> x1 >> y1;
    cout << "Input point B (x2 y2): ";
    cin >> x2 >> y2;
    cout << "Input point C (x3 y3): ";
    cin >> x3 >> y3;

    a = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    b = sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2));
    c = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));
    s = (a + b + c) / 2;

    area = sqrt(s * (s - a) * (s - b) * (s - c));

    cout << "The area of the triangle ABC is: " << area;

    return 0;
}