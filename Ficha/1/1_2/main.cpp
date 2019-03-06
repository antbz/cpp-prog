#include <iostream>

using namespace std;

int main() {
    streamsize ogPrecision = cout.precision();
    double A;
    double B;
    double C;
    double avg;

    cout << "A? ";
    cin >> A;
    cout << "B? ";
    cin >> B;
    cout << "C? ";
    cin >> C;

    avg = (A + B + C) / 3;
    cout.precision(20);
    cout << "average\t= " << avg << "\n";
    cout << "A-average\t= " << A-avg <<"\n";
    cout << "B-average\t= " << B-avg <<"\n";
    cout.precision(ogPrecision);
    cout << "C-average\t= " << C-avg ;

    return 0;
}