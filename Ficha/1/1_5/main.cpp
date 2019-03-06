#include <iostream>
#include <ctime>

using namespace std;

int main() {
    unsigned int h1, m1, s1, h2, m2, s2, hs, ms, ss, ds;

    cout << "Tempo 1 (horas minutos segundos) ? ";
    cin >> h1 >> m1 >> s1;
    cout << "Tempo 2 (horas minutos segundos) ? ";
    cin >> h2 >> m2 >> s2;

    ss = s1 + s2;
    ms = m1 + m2 + (ss / 60);
    hs = h1 + h2 + (ms / 60);
    ds = hs / 24;

    ss %= 60;
    ms %= 60;
    hs %= 24;

    cout << "Soma dos tempos: ";
    if (ds != 0) {
        if (ds == 1)
            cout << ds << " dia, ";
        else
            cout << ds << " dias, ";
    }
    if (hs != 0) {
        if (hs == 1)
            cout << hs << " hora, ";
        else
            cout << hs << " horas, ";
    }
    if (ms != 0) {
        if (ms == 1)
            cout << ms << " minuto, ";
        else
            cout << ms << " minutos, ";
    }
    if (ss != 0) {
        if (ss == 1)
            cout << ss << " segundo";
        else
            cout << ss << " segundos";
    }
    return 0;
}