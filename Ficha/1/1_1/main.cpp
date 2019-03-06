#include <iostream>

using namespace std;

int main() {
    char letter;
    const char STOP = '#';

    do {
        cout << "Input a letter (# - quit): ";
        cin >> letter;
        if (letter != STOP)
            cout << "ASCII(" << letter << ") = " << (int)letter << '\n';
    } while (letter != STOP);

    return 0;
}