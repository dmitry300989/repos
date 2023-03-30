// hosaam_and_combination.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int t;
    std::cin >> t;
    long long n = 0;
    for (int i = 0; i < t; ++i)
    {
        std::cin >> n;
        std::vector<int> vi(n);
        for (int j = 0; j < n; ++j)
        {
            std::cin >> vi[j];
        }
        auto itMaxElem = std::max_element(vi.begin(), vi.end());
        auto itMinElem = std::min_element(vi.begin(), vi.end());
        if (*itMaxElem != *itMinElem)
        {
            long long nMax = std::count(vi.begin(), vi.end(), *itMaxElem);
            long long nMin = std::count(vi.begin(), vi.end(), *itMinElem);
            std::cout << nMax * nMin * 2 << std::endl;
        }
        else
        {
            std::cout << n * (n-1) << std::endl;
        }
    }
    return 0;
}
