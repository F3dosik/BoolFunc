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
        if (remain <= 0)
            remain = 64;
        else
            remain = 64 - remain;
        vec[blocks - 1 - i] = ull_str(line.substr(start, remain));
    }
    
}

BoolList::BoolList(BoolList& bl)
{
    vec = bl.vec;
    length = bl.length;
    blocks = bl.blocks;
}

bool BoolList::operator[] (unsigned int i)
{
    if (i > length)
        return 0;

    auto t = i >> 6;
    auto ind = i - (t << 6);
    ull bit = 1;
    bit <<= (ind);
     
    //return ((vec[blocks - t - 1]) & (1 << ind)); // с какого-то чёрта это выдаёт неверный результат
    return ((vec[blocks - t - 1]) & bit);
}

void BoolList::show_list()
{
    for (int i = 0; i < blocks; i++)
        print_bin(vec[i]);
    println("");
}
