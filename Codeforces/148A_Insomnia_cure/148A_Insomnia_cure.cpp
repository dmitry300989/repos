// 148A_Insomnia_cure.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int d, k, l, m, n;
    std::cin >> k >> l >> m >> n >> d;

    vector<int>  damaged(d+1,0); // create a boolean array to track damaged dragons
    int count = 0; // initialize count of damaged dragons to 0

    // iterate through all dragons and apply the actions as described
    for (int i = 1; i <= d; i++) {
        if (i % k == 0) {
            if (damaged[i] == 0)
                count++;
            damaged[i] = 1;
        }
        if (i % l == 0) {
            if (damaged[i] == 0)
                count++;
            damaged[i] = 1;
        }
        if (i % m == 0) {
            if (damaged[i] == 0)
                count++;
            damaged[i] = 1;
        }
        if (i % n == 0) {
            if (damaged[i] == 0)
                count++;
            damaged[i] = 1;
        }
    }

    std::cout << count << std::endl; // output the count of damaged dragons
}
