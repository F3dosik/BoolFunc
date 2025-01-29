#include "BoolList.h"
#include <string>

typedef unsigned long long ull;

BoolList::BoolList(unsigned int len)
{
    length = len;
    if (length == 0)
        length++;
    blocks = length >> 6;
    blocks += (blocks << 6) != length;

    vec = new ull[blocks];

    for (int i = 0; i < blocks; i++)
        vec[i] = 0;
}

BoolList::BoolList(std::string line)
{
    length = line.size();
    if (length == 0)
        length++;
    
    int len = length;

    blocks = length >> 6;
    blocks += (blocks << 6) != length;

    vec = new ull[blocks];


    for (int i = 0; i < blocks; i++)
    {
        auto start = std::max(0, len - (i + 1) * 64);
        int remain = -(len - (i + 1) * 64);
        print((long long int)start);
        print(" ");
        println((long long int)remain);
        if (remain <= 0)
            remain = 64;
        else
            remain = 64 - remain;
        vec[blocks - 1 - i] = ull_str(line.substr(start, remain));
    }
    
}

void BoolList::show_list()
{
    for (int i = 0; i < blocks; i++)
        print_bin(vec[i]);
    println("");
}
