#include "common.h"
#include <iostream>
#include <string>

typedef unsigned long long ull;

std::string str_bin(ull n)
{
    std::string line = "";
    bool first_one = false;
    bool temp = false;

    while (temp != 1)
    {
        temp = (n - ((n << 1) >> 1) >> 63);
        n <<= 1;
    }
    line += '1';
    while (n != 0)
    {
        temp = (n - ((n << 1) >> 1) >> 63);
        line += char('0' + temp);
        n <<= 1;
    }
    return line;
}

std::string str_bin(ull* arr, unsigned int size)
{
    std::string line = "";
    for (int i = 0; i < size; i++)
    {
        line += str_bin(arr[i]);
    }
    return line;
}

void print(std::string line)
{
    std::cout << line;
}

void print(ull n)
{
    std::cout << n;
}

void print_bin(ull n)
{
    while (n != 0)
    {
        print((n - ((n << 1) >> 1)) >> 63);
        n <<= 1;
    }
}

void println(std::string line)
{
    std::cout << line << std::endl;
}

void println(ull n)
{
    std::cout << n << std::endl;
}

unsigned int weight(ull n)
{
    ull w = n;
    w = w - ((w >> 1) & 0x5555555555555555);
    w = (w & 0x3333333333333333) + ((w >> 2) & 0x3333333333333333);
    w = (w + (w >> 4)) & 0x0f0f0f0f0f0f0f0f;
    w = w + (w >> 8);
    w = w + (w >> 16);
    w = w + (w >> 32);
    return w & 0x7f;
}

unsigned int weight(ull* arr, unsigned int size)
{
    ull w = 0;
    for (int i = 0; i < size; i++)
        w += weight(arr[i]);
    return w;
}
