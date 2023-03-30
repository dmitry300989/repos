// TooLongWords.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

int main()
{
    int n;
    std::cin >> n;
    std::string word, res;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> word;
        int k = word.length();
        if (k > 10)
        {
            res = ((word[0]) + std::to_string(k - 2) + (word[k - 1]));
        }
        else
        {
            res = word;
        }
        std::cout << res << std::endl;
    }
    return 0;
}
