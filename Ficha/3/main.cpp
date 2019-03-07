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

int main() {

}