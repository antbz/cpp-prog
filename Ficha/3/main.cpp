#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

// ex3_4
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

    reduceFrac(res_num, res_den);
    writeFrac(res_num, res_den);
}

int ex3_5() {
    int num, den;

//    num = 42;
//    den = 28;
//    reduceFrac(num, den);
//    writeFrac(num, den);

    calcFrac(1, 2, 1, 3, '+');

    return 0;
}

// ex3_6
bool leapYear(int year) {
    if (year % 400 == 0)
        return true;
    else if (year % 100 == 0)
        return false;
    else if (year % 4 == 0)
        return true;
    else
        return false;
}

int daysInMonth(int month, int year) {
    if (month < 1 || month > 12)
        return -1;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
        || month == 10 || month == 12)
        return 31;
    else if (month == 2) {
        if (leapYear(year))
            return 29;
        else
            return 28;
    } else
        return 30;
}

int weekDay(int year, int month, int day) {
    int wday, s, a, c;
    int month_code[12][2] = {
            {0, 6},
            {3, 2},
            {3, 3},
            {6, 6},
            {1, 1},
            {4, 4},
            {6, 6},
            {2, 2},
            {5, 5},
            {0, 0},
            {3, 3},
            {5, 5}
    };

    s = year / 100;
    a = year - s * 100;
    c = month_code[month - 1][leapYear(year)];

    wday = (int(floor(5 * a / 4)) + c + day - 2 * (s % 4) + 7) % 7;

    return wday;
}

void monthCalendar(int month, int year) {
    string months[12] = {"January", "February", "March",
                         "April", "May", "June", "July",
                         "August", "September", "October",
                         "November", "December"};
    int space = 6;
    int startDay, numberOfDays, currentPos;

// Formats the header of the calendar
    cout << months[month - 1] << " / " << year << endl;
    cout << "Sun" << setw(space) << "Mon" << setw(space) << "Tue" << setw(space) << "Wed"
    << setw(space) << "Thu" << setw(space) << "Fri" << setw(space) << "Sat" << endl;

// Writes the first month of the calendar with necessary white space

    startDay = (weekDay(year, month, 1) + 6) % 7;       //Calculates the number of leading spaces for the 1st day of the month
    currentPos = startDay;      //Sets a variable that tracks the position on the calendar
    numberOfDays = daysInMonth(month, year);
//    cout << endl << currentPos << endl;

    for (int i = startDay; i >= 1; i--) {
        cout << "   " << setw(space);
    }
    if (currentPos == 0)
        cout << setw(3);
    cout << 1;

    for (int i = 2; i <= numberOfDays; i++) {
        currentPos++;
        if (currentPos > 6) {
            cout << endl;
            currentPos = 0;
        }
        if (currentPos == 0)
            cout << setw(3) << i;
        else
            cout << setw(space) << i;

    }
}

void yearCalendar(int year) {
    for (int i = 1; i <=12; i++) {
        monthCalendar(i, year);
        cout << endl << endl << "--------------------------------" << endl << endl;
    }
}

int ex3_6() {
    yearCalendar(2004);
}