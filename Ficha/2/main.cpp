#include <iostream>
#include <cmath>

using namespace std;

int ex22() {
    double a, b, c;

    cout << "Please input 3 numbers: ";
    cin >> a >> b >> c;

/*  2.2.a
    if (a > b)
        swap(a, b);
    if (a > c)
        swap(a, c);
    if (b > c)
        swap(b, c);

    cout << "Min: " << a << endl << "Max: " << c;
*/
/*  2.2.b
    if (a < b)
        swap(a, b);
    if (a < c)
        swap(a, c);
    if (b < c)
        swap(b, c);

    cout << "In descending order: " << a << " " << b << " " << c;
*/
    if (a > b)
        swap(a, b);
    if (a > c)
        swap(a, c);
    if (b > c)
        swap(b, c);
    if (a + b <= c)
        cout<<"Not a triangle";
    else
        cout<<"Illoominooti";

    return 0;
}

int ex23() {
    const char QUIT = 'q';
    double n1, n2, result;
    char operand, qt;

    while (true) {

        cout << "Input (q to quit): ";

        qt = cin.peek();
        if (qt == QUIT)
            break;

        cin >> n1 >> operand >> n2;

        switch (operand) {
            case '+':
                result = n1 + n2;
                break;
            case '-':
                result = n1 - n2;
                break;
            case '*':
                result = n1 * n2;
                break;
            case '/':
                result = n1 / n2;
                break;
        }

        cout << "Result: " << result << endl;
        cin.clear();
    }

    return 0;
}

int ex26() {
    int n = 2, i, p = 0;
    bool isPrime;

//    cout << "Input a number: ";
//    cin >> n;

//    while (p < 100) {
//        isPrime = true;
//        for (i = 2; i <= sqrt(n); i++) {
//            if (n % i == 0) {
//                isPrime = false;
//                break;
//            }
//        }
//        if (isPrime) {
//            p++;
//            cout << p << " " << n << endl;
//        }
//        n++;
//    }

    for (n; n < 1000000; n++) {
        isPrime = true;

        for (i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
            cout << n << endl;
    }

//    cout << "O número é primasss!";

    return 0;
}

double deg2rad(double angle) {
    const double pi = 3.14159265358979323846264;
    return (pi * angle) / 180;
}


int main() {
    float min, max, step;

    cout << "Table min, max and step: ";
    cin >> min >> max >> step;

    cout << "ang\t" << "sen\t" << "cos\t" << "tan" << endl;

    cout.precision(6);
    cout << fixed;

    cout << cos(deg2rad(15));

    return 0;
}