#include "pch.h"
#include "Calculator.h"
#include <iostream>

int add(const long long a, const long long b)
{
	return a + b;
}

int subtract(
    const long long a, const long long b)
{
    return a - b;
}

int multiply(
    const long long a, const long long b)
{
    return a * b;
}

double divide(
    const double a, const double b)
{
    if (b == 0)
    {
        std::cout << "ERROR: Division by null" << '\n';
        return 0;
    }
    else
        return a / b;
}