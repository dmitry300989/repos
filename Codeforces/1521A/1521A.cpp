// 1521A.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int d, k, l, m, n;
    std::cin >> k >> l >> m >> n >> d;

    bool damaged[d + 1] = { false }; // create a boolean array to track damaged dragons
    int count = 0; // initialize count of damaged dragons to 0

    // iterate through all dragons and apply the actions as described
    for (int i = 1; i <= d; i++) {
        if (i % k == 0) {
            damaged[i] = true;
            count++;
        }
        if (i % l == 0) {
            damaged[i] = true;
            count++;
        }
        if (i % m == 0) {
            damaged[i] = true;
            count++;
        }
        if (i % n == 0) {
            damaged[i] = true;
            count++;
        }
    }

    std::cout << count << std::endl; // output the count of damaged dragons

    return 0;
}
