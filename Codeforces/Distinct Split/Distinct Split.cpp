// Distinct Split.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int SolutionByMapAndSet(unsigned int n, string &s)
{
    unordered_set<char> sc;
    unordered_map<char, int> dict;
    for (auto& c : s)
    {
        dict[c]++;
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (dict.size() == n - i)
            break;
        dict[s[i]]--;
        sc.insert(s[i]);
        if (dict[s[i]] == 0)
        {
            dict.erase(s[i]);
        }
    }
    return dict.size() + sc.size();
}

int sol(unsigned int n, string& s)
{
    unordered_map<char, int> dict;
    for (auto& c : s)
    {
        dict[c]++;
    }
    unordered_map<char, int> dict2;
    int max = 0;
    int sz = 0;
    for (auto& c : s)
    {
        dict2[c]++;
        dict[c]--;
        if (dict[c] == 0)
            dict.erase(c);
        sz = dict2.size() + dict.size();
        max = max > sz ? max : sz;
    }
    return max;
}

int main() {
    unsigned int t = 0;
    cin >> t;
    //t = 1;
    while (t--)
    {
        unsigned int n = 0;
        cin >> n;
        //n = 7;
        string s;
        cin >> s;
        //s = "abcabcd";
        cout << sol(n, s) << endl;
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы ccabzabz
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
