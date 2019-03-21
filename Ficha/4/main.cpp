#include <iostream>
#include <string>
#include <string.h>

using namespace std;

// ex4_1
bool isHydroxide(char compound[]) {
    int len = strlen(compound);
    if (compound[len-2] == 'O' && compound[len-1] == 'H')
        return true;
    return false;
}

int ex4_1() {
//    cout << isHydroxide("MgOH");
}

// ex4_2
bool sequenceSearch(string s, int nc, char c) {
    string seq = "";
    for (int i = 0; i < nc; i++)
        seq.push_back(c);
    if (s.find(seq) == string::npos)
        return false;
    return true;
}

int ex4_2() {
    cout << sequenceSearch("OooppA", 2, 'o');
}

// ex4_3
void decompose(string compound) {
    string element;
    for (int i = 0; i <= compound.length(); i++) {
        if (isupper(compound[i])) {
            if (i != 0)
                cout << element << endl;
            element = "";
            element += compound[i];
        }
        else if (isalpha(compound[i]))
            element += compound[i];
    }
    cout << element;
}

int ex4_3() {
    decompose("Na3Cl8I9O");
    return 0;
}

// ex4_6
void readIntArray(int a[], int nElem) {
    for (int i = 0; i < nElem; i++) {
        cout << i << ": ";
        cin >> a[i];
    }
}

int searchValueInIntArray(const int a[], int nElem, int value) {
    for (int i = 0; i < nElem; i++) {
        if (value == a[i])
            return i;
    }
    return -1;
}

int main() {
    int a[5];
    readIntArray(a, 5);
    cout << searchValueInIntArray(a, 5, 3);
}