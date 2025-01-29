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
    length = bl.length;
    blocks = bl.blocks;
    for (int i = 0; i < blocks; i++)
        vec[i] = bl.vec[i];
}

void BoolList::operator= (const BoolList bl)
{
    length = bl.length;
    blocks = bl.blocks;
    for (int x = 0; x < blocks; x++)
        vec[x] = bl.vec[x];
}

void BoolList::operator= (BoolList& bl)
{
    length = bl.length;
    blocks = bl.blocks;
    for (int x = 0; x < blocks; x++)
        vec[x] = bl.vec[x];
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

const BoolList BoolList::operator<< (unsigned int i)
{
    BoolList bl_(length);
    for (int x = 0; x < blocks; x++)
        bl_.vec[x] = vec[x];

    if (i == 0)
        return bl_;

    if (i < 64)
    {
        bl_.vec[blocks - 1] <<= i;
        for (int x = bl_.blocks - 2; x >= 0; x--)
        {
            bl_.vec[x] = (vec[x + 1] >> (64 - i)) | (vec[x] << i);
        }
    }
    else if (i >= 64)
    {
        bl_ = bl_ << 63;
        i -= 63; 
        bl_ = bl_ << i;
    }
    
    return bl_;
}

const BoolList BoolList::operator>> (unsigned int i)
{
    BoolList bl_(length);
    for (int x = 0; x < blocks; x++)
        bl_.vec[x] = vec[x];

    if (i == 0)
        return bl_;

    if (i < 64)
    {
        bl_.vec[0] >>= i;
        for (int x = 1; x < blocks; x++)
        {
            bl_.vec[x] = (vec[x - 1] << (64 - i)) | (vec[x] >> i);
        }
    }
    else if (i >= 64)
    {
        bl_ = bl_ >> 63;
        i -= 63;
        bl_ = bl_ >> i;
    }
    return bl_;
}

void BoolList::show_list()
{
    for (int i = 0; i < blocks; i++)
        print_bin(vec[i]);
    println("");
}
