#pragma once

#ifdef CALCULATOR_EXPORTS
#define CALCULATOR_API __declspec(dllexport)
#else
#define CALCULATOR_API __declspec(dllimport)
#endif

extern "C" CALCULATOR_API int add(
    const long long a, const long long b);

extern "C" CALCULATOR_API int subtract(
    const long long a, const long long b);

extern "C" CALCULATOR_API int multiply(
    const long long a, const long long b);

extern "C" CALCULATOR_API double divide(
    const double a, const double b);
