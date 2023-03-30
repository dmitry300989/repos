// Van_Eck_seq.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <array>

#include <chrono>
using namespace std::chrono;

void run()
{
    int A1 = 0;
    int N = 1000000;
    std::map <int, int> keys;
    for (int n = 1; n < N; n++)
    {
        int* p = &keys[A1];
        A1 = (*p) ? (n - *p) : 0;
        *p = n;
    }
    std::cout << A1 << '\n';
}

void run2()
{
    int a1 = 0;
    int n = 1000000;

    int m = 60;
    std::vector<int> v(1000001, 0);
    std::vector<int> place(1000001, -1);
    v[0] = a1;
    v[1] = 0;
    int k = 0;
    place[a1] = 0;
    for (int i = 1; i < n; ++i)
    {
        if (place[v[i]] != -1)
        {
            v[i + 1] = i - place[v[i]];
        }
        else
        {
            v[i + 1] = 0;
        }
        place[v[i]] = i;
        k = v[i];
        //std::cerr << v[i] << " ";
    }
    std::cerr << k << " ";
}

int main()
{
    auto start = high_resolution_clock::now();
    //run();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // To get the value of duration use the count()
    // member function on the duration object
    std::cout << duration.count() << std::endl;
    std::vector<int> v(1,1);
    std::cerr << sizeof(v) << '\n';
    std::map<int, int> m;
    m[0] = 1;
    std::cerr << sizeof(m) << '\n';
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
