#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double round(double x, unsigned n) {
    return floor(x * pow(10, n) + 0.5) / pow(10, n);
}

int ex3_4() {
    double num;
    int n;
    cout << "Number: ";
    cin >> num;
    cout << "Decimal places: ";
    cin >> n;
    cout << setprecision(n) << fixed << round(num, n);
    return 0;
}

bool readFrac(int &numerator, int &denominator) {
    char separator;
    cin >> numerator >> separator >> denominator;
    if (separator == '/' && denominator != 0)
        return true;
    else
        numerator = 0;
        denominator = 0;
        return false;
}

void writeFrac(int numerator, int denominator) {
    cout << numerator << "/" << denominator;
}

int gcd(int a, int b) {
    if (a < b)
        swap(a, b);
    while (a % b != 0) {
        swap(a, b);
        b %= a;
    }
    return b;

}

int main() {
    int num, den;
    cout << gcd(25,5);
}