// B_BerSU_Ball.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n = 0, m = 0;
    std::cin >> n;
    std::vector<int> boys(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> boys[i];
    }
    std::cin >> m;
    std::vector<int> girls(m);
    for (int j = 0; j < m; ++j)
    {
        std::cin >> girls[j];
    }
    std::sort(boys.begin(), boys.end());
    std::sort(girls.begin(), girls.end());
    auto pIterBoy = boys.begin();
    auto pIterGril = girls.begin();
    int diff = 0;
    int cnt = 0;
    while (1)
    {
        diff = *pIterBoy - *pIterGril;
        if (abs(diff) <= 1)
        {
            cnt++;
            if (pIterGril != girls.end())
                pIterGril++;
            if (pIterBoy != boys.end())
                pIterBoy++;
        }
        else
        {
            if (*pIterBoy > *pIterGril)
                pIterGril++;
            else if (*pIterBoy < *pIterGril)
                pIterBoy++;
        }
        if (pIterBoy == boys.end() || pIterGril == girls.end())
            break;
    }
    std::cout << cnt;
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
