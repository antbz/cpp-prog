#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int ex2_2() {
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

int ex2_3() {
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

int ex2_4() {
    float peso, custo;

    cout << "Peso da mercadoria: ";
    cin >> peso;

    if (peso < 500)
        custo = 5;
    else if (peso <= 1000)
        custo = 5 + ((peso - 500) / 100) * 1.5;
    else
        custo = 12.5 + ((peso - 1000) / 250) * 5;

    cout << fixed << setprecision(2) << "Custo de transporte (euros): " << custo;

    return 0;
}

int ex2_6() {
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

//    cout << "O número é primo!";

    return 0;
}

double deg2rad(double angle) {
    const double pi = 3.14159265358979323846264;
    return (pi * angle) / 180;
}

int ex2_7() {
    double min, max, step, i;

    cout << "Table min, max and step: ";
    cin >> min >> max >> step;

    cout << "ang" << setw(10) << "sen" << setw(10) << "cos" << setw(10) << "tan" << endl;

//    cout.precision(6);
//    cout << fixed;

    for (i = min; i <= max; i += step) {
        cout << setw(5) << defaultfloat << internal << i << setw(10) << setprecision(6) << fixed << sin(deg2rad(i)) << setw(10) << cos(deg2rad(i)) << setw(10);
        if (i != 90)
            cout << tan(deg2rad(i)) << endl;
        else
            cout << "infinito";
    }

    return 0;
}

double compound_int(double n, double q, double j, double k = 1) {
    return q * pow((1 + j/(100 * k)), n);
}

int ex2_8() {
    double n, q, j, available;

    cout << "# de anos do depósito: ";
    cin >> n;
    cout << "Quantia depositada: ";
    cin >> q;
    cout << "Taxa anual nominal (%): ";
    cin >> j;

    available = compound_int(n, q, j);

    cout << endl << "Quantia disponível ao fim de " << n << " anos: " << available;

    return 0;
}

int ex2_9() {
    int input, sum = 0, big, small, size = 0;
    double average;

    cout << "Input sequence (END = f): ";
    cin >> input;

    while (!cin.fail()) {
        sum += input;
        size++;
        if (size == 1) {
            big = input;
            small = input;
        }
        if (input > big)
            big = input;
        if (input < small)
            small = input;
        cin >> input;
    }

    average = double(sum) / double(size);

    cout << endl << "Sum: " << sum << endl << "Size: " << size << endl << "Max: " << big << endl << "Min: " << small;
    cout << endl << "Average: " << average;

    return 0;
}

int ex2_10() {
    int num, reverse = 0, original;

    cout << "Number? ";
    cin >> num;

    original = num;

    while (num != 0) {
        reverse = reverse * 10 + num % 10;
        num /= 10;
    }

    if (original == reverse)
        cout << "The number is a palindrome!";
    else
        cout << "The number is not a palindrome";

    return 0;
}

int ex2_11() {
    double i, sum = 0, term = 1, x = 1;
    int n = 10;

    for (i = 0; i <= n; i++) {
        if (i != 0)
            term *= 1/i;
        sum += pow(-1, i) * term;
    }

    cout << sum;

    return 0;
}

void primeFactors(int n) {
    cout << n << "=";
    for (int i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            cout << i << "x";
            n = n / i;
        }
    }
    cout << n;
}

int ex2_13() {
    primeFactors(20);
    return 0;
}

double heron_sqrt(double n, double delta, double nMaxIter, double rq = 1) {
    for (nMaxIter; nMaxIter >= 0; nMaxIter--) {
        rq = (rq + n / rq) / 2;
        if (abs(n - pow(rq, 2)) <= delta)
            break;
    }

    return rq;
}

int decCases(double delta) {
    int nCases = 0;

    for (delta; delta < 1; delta *= 10) {
        nCases++;
    }

    return nCases;
}

int ex2_14() {
    double n, delta, nMaxIter;

    cout << "Precision: ";
    cin >> delta;
    cout << "Maximum iteration: ";
    cin >> nMaxIter;
    cout << "n? ";
    cin >> n;

    cout << setprecision(decCases(delta)) << fixed << heron_sqrt(n, delta, nMaxIter) << endl << sqrt(n);
    return 0;
}

int ex2_15() {
    int time_init, time_ans, num1, num2, ans, tdelta;
    srand(time(NULL));

    num1 = rand() % 8 + 2;
    num2 = rand() % 8 + 2;

    cout << num1 << "x" << num2 << "=";
    time_init = time(NULL);
    cin >> ans;
    time_ans = time(NULL);

    tdelta = time_ans - time_init;

    if (ans != num1*num2)
        cout << "WRONG!";
    else if (tdelta < 5)
        cout << "Very well!";
    else if (tdelta <= 10)
        cout << "Ok...";
    else
        cout << "Not good enough...";

    return 0;
}