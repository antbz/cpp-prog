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

// ex3_5
int gcd(int a, int b) {
    if (a < b)
        swap(a, b);
    while (a % b != 0) {
        swap(a, b);
        b %= a;
    }
    return b;
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
    cout << numerator << "/" << denominator << endl;
}

void reduceFrac(int &numerator, int &denominator) {
    int greatest;
    greatest = gcd(numerator, denominator);
    numerator /= greatest;
    denominator /= greatest;
}

void calcFrac(int num1, int den1, int num2, int den2, char op) {
    int res_num, res_den;

    switch (op) {
        // Addition
        case '+':
            res_num = num1 * den2 + num2 * den1;
            res_den = den1 * den2;
            break;

        //Subtraction
        case '-':
            res_num = num1 * den2 - num2 * den1;
            res_den = den1 * den2;
            break;

        //Multiplication
        case '*':
            res_num = num1 * num2;
            res_den = den1 * den2;
            break;

        //Division
        case '/':
            res_num = num1 * den2;
            res_den = num2 * den1;
            break;
    }
    cout << res_num << endl;
    cout << res_den << endl;
    writeFrac(res_num, res_den);
    reduceFrac(res_num, res_den);
    writeFrac(res_num, res_den);
}

int ex3_5() {
    int num, den;

//    num = 42;
//    den = 28;
//    reduceFrac(num, den);
//    writeFrac(num, den);

    calcFrac(1,2,1,3,'+');

    return 0;
}

