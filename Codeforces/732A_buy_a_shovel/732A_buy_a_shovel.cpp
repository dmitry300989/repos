// 732A_buy_a_shovel.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int k = 0, r = 0;
	cin >> k;
	cin >> r;
	int res = 0;
	for (int i = 1; i <= 10; ++i)
	{
		int t = ((k % 10) * i) % 10;
		if (t == r || t == 0)
		{
			res = i;
			break;
		}
	}
	cout << res << endl;
	return 0;
}
