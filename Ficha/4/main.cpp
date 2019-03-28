#include <iostream>
#include <string>
#include <string.h>
#include <array>
#include <vector>
#include <fstream>

using namespace std;


// ex4_1
bool isHydroxide(char compound[]) {
    int len = strlen(compound);
    if (compound[len - 2] == 'O' && compound[len - 1] == 'H')
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
        } else if (isalpha(compound[i]))
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

int searchMultValuesInIntArray(const int a[], int nElem, int value, int index[]) {
    int found = 0;
    for (int i = 0; i < nElem; i++) {
        if (value == a[i]) {
            index[found] = i;
            found++;
        }
    }
    return found;
}

int ex4_6() {
    int a[5];
    int index[5];
    readIntArray(a, 5);
    cout << searchMultValuesInIntArray(a, 5, 3, index);
}

// ex4_7
void readIntVector(vector<int> &v) {
    int tmp;
    int i = 0;
    cout << i << ": ";
    cin >> tmp;
    while (!cin.eof()) {
        v.push_back(tmp);
        i++;
        cout << i << ": ";
        cin >> tmp;
    }
}

vector<int> searchMultValuesInIntVector(const vector<int> &v, int value) {
    vector<int> found;
    for (int i = 0; i < v.size(); i++) {
        if (value == v[i]) {
            found.push_back(i);
        }
    }
    return found;
}

int ex4_7() {
    vector<int> v, f;
    readIntVector(v);
    f = searchMultValuesInIntVector(v, 4);
    cout << endl << "Found 4 in the following indexes" << endl;
    for (int i = 0; i < f.size(); i++) {
        cout << f[i] << "  ";
    }
}

// ex4_8
void bubblesort(vector<string> &v) {
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = 0; j < v.size() - 1 - i; j++) {
            int cmp = v[j].compare(v[j + 1]);
            if (cmp > 0) {
                string tmp = v[j + 1];
                v[j + 1] = v[j];
                v[j] = tmp;
            }
        }
    }
}

int ex4_8() {
    vector<string> ree = {"Amanda", "Daniel", "Adao", "Pass", "Edda"};
    bubblesort(ree);
    for (int i = 0; i < ree.size(); i++)
        cout << i << ": " << ree[i] << endl;
    return 0;
}

// ex4_9
int binarySearch(const vector<string> &v, string value) {
    int bottom = 0;
    int top = v.size() - 1;
    int middle = top / 2;

    do {
        if (v[middle] == value)
            return middle;
        else if (v[middle] < value)
            bottom = middle + 1;
        else
            top = middle - 1;
        middle = (bottom + top)/2;
    } while (bottom <= top);

    return -1;
}

int ex4_9() {
    vector<string> ree = {"Amanda", "Daniel", "Adao", "Pass", "Edda"};
    bubblesort(ree);
    cout << binarySearch(ree, "Edda");
//    for (int i = 0; i < ree.size(); i++)
//        cout << i << ": " << ree[i] << endl;
    return 0;
}

// ex4_10
void removeDuplicates(vector<int> &v) {
    int i = 0;
    while (i < v.size()) {
        int j = i + 1;
        while (j < v.size()) {
            if (v[i] == v[j])
                v.erase(v.begin() + j);
            else
                j++;
        }
        i++;
    }
}

int ex4_10() {
    vector<int> mee = {1, 1, 1,2,3,1,2, 2, 2,3,1,2,3};
    removeDuplicates(mee);
    for (int i = 0; i < mee.size(); i++)
        cout << i << ": " << mee[i] << endl;
}