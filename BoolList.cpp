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

    blocks = length >> 6;
    blocks += (blocks << 6) != length;

    vec = new ull[blocks];


    for (int i = 0; i < blocks; i++)
    {
        auto start = std::max(0, (int)length - (i + 1) * 64);
        auto end   = (int)length - i * 64 - 1;
        if (end != start)
            vec[blocks - 1 - i] = ull_str(line.substr(start, end));
        else
            vec[blocks - 1 - i] = (line[start] == '0') ? 0 : 1;
    }

    
}

void BoolList::show_list()
{
    for (int i = 0; i < blocks; i++)
        print_bin(vec[i]);
    println("");
}
