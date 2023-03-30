// Asterisk-Minor Template.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;

bool is_match(const string& s, const string& t) {
    if (s.length() != t.length()) return false;
    for (int i = 0; i < s.length(); i++) {
        if (t[i] != '*' && s[i] != t[i]) return false;
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    T = 1;
    while (T--) {
        string a, b;
        cin >> a >> b;
        int n = a.length(), m = b.length();
        int asterisks = 0, non_asterisks = 0;
        for (char c : a) {
            if (c == '*') asterisks++;
            else non_asterisks++;
        }
        for (char c : b) {
            if (c == '*') asterisks++;
            else non_asterisks++;
        }
        if (asterisks < non_asterisks) {
            cout << "NO\n";
            continue;
        }
        int k = n + m - non_asterisks;
        string t(k, '*');
        int i = 0, j = 0;
        for (char c : a) {
            if (c == '*') continue;
            t[i++] = c;
        }
        for (char c : b) {
            if (c == '*') continue;
            if (is_match(t, string(j, '*') + c + string(k - j - 1, '*'))) {
                t[j++] = c;
            }
            else {
                t[j++] = '*';
            }
        }
        for (char c : a) {
            if (c == '*') continue;
            if (!is_match(string(j, '*') + c + string(k - j - 1, '*'), t)) {
                cout << "NO\n";
                goto next_case;
            }
            j++;
        }
        for (char c : b) {
            if (c == '*') continue;
            if (!is_match(string(j, '*') + c + string(k - j - 1, '*'), t)) {
                cout << "NO\n";
                goto next_case;
            }
            j++;
        }
        cout << "YES\n" << t << "\n";
    next_case:;
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
