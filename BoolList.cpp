#include "BoolList.h"
#include <string>

typedef unsigned long long ull;

BoolList::BoolList(unsigned int len)
{
    auto length = len;
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
    int length = line.size();
    if (length == 0)
        length++;
    
    blocks = length >> 6;
    blocks += (blocks << 6) != length;

    vec = new ull[blocks];


    for (int i = 0; i < blocks; i++)
    {
        auto start = std::max(0, length - (i + 1) * 64);
        int remain = -(length - (i + 1) * 64);
        if (remain <= 0)
            remain = 64;
        else
            remain = 64 - remain;
        vec[blocks - 1 - i] = ull_str(line.substr(start, remain));
    }
    
}

BoolList::BoolList(BoolList& bl)
{
    blocks = bl.blocks;
    vec = new ull[blocks];
    for (int i = 0; i < blocks; i++)
        vec[i] = bl.vec[i];
}

BoolList::BoolList(const BoolList* bl)
{
    blocks = bl->blocks;
    vec = new ull[blocks];
    for (int i = 0; i < blocks; i++)
        vec[i] = bl->vec[i];
}

void BoolList::operator= (BoolList bl)
{
    delete[] vec;
    vec = new ull[bl.blocks];
    blocks = bl.blocks;
    for (int x = 0; x < bl.blocks; x++)
        vec[x] = bl.vec[x];
}

//void BoolList::operator= (BoolList& bl)
//{
//    length = bl.length;
//    blocks = bl.blocks;
//    for (int x = 0; x < blocks; x++)
//        vec[x] = bl.vec[x];
//}


bool BoolList::operator[] (unsigned int i)
{
    if (i > 64 * blocks)
        return 0;

    auto t = i >> 6;
    auto ind = i - (t << 6);
    ull bit = 1;
    bit <<= (ind);
     
    //return ((vec[blocks - t - 1]) & (1 << ind)); // с какого-то чёрта это выдаёт неверный результат
    return ((vec[blocks - t - 1]) & bit);
}

BoolList BoolList::operator<< (unsigned int i) const
{
    auto cp = i;
    BoolList bl_(64 * blocks);
    for (int x = 0; x < blocks; x++)
        bl_.vec[x] = vec[x];

    if (cp == 0)
        return bl_;

    if (cp < 64)
    {
        bl_.vec[blocks - 1] <<= cp;
        for (int x = bl_.blocks - 2; x >= 0; x--)
        {
            bl_.vec[x] = (vec[x + 1] >> (64 - cp)) | (vec[x] << cp);
        }
    }
    else if (cp >= 64)
    {
        bl_ = bl_ << 63;
        cp -= 63; 
        bl_ = bl_ << cp;
    }
    
    return bl_;
}

BoolList BoolList::operator>> (unsigned int i) const
{
    auto cp = i;
    BoolList bl_(64 * blocks);
    for (int x = 0; x < blocks; x++)
        bl_.vec[x] = vec[x];

    if (cp == 0)
        return bl_;

    if (cp < 64)
    {
        bl_.vec[0] >>= cp;
        for (int x = 1; x < blocks; x++)
        {
            bl_.vec[x] = (vec[x - 1] << (64 - cp)) | (vec[x] >> cp);
        }
    }
    else if (cp >= 64)
    {
        bl_ = bl_ >> 63;
        cp -= 63;
        bl_ = bl_ >> cp;
    }
    return bl_;
}

BoolList BoolList::operator| (BoolList bl) const
{
    BoolList a(bl);
    BoolList b(this);
    if (a.blocks < b.blocks)
        a.stretch(b.blocks);
    else if (b.blocks < a.blocks)
        b.stretch(a.blocks);

    for (int i = 0; i < a.blocks; i++)
        a.vec[i] = (a.vec[i] | b.vec[i]);

    return a;
}

BoolList BoolList::operator& (BoolList bl) const
{
    BoolList a(bl);
    BoolList b(this);
    if (a.blocks < b.blocks)
        a.stretch(b.blocks);
    else if (b.blocks < a.blocks)
        b.stretch(a.blocks);

    for (int i = 0; i < a.blocks; i++)
        a.vec[i] = (a.vec[i] & b.vec[i]);

    return a;
}

void BoolList::show_list()
{
    for (int i = 0; i < blocks; i++)
        print_bin(vec[i]);
    println("");
}

void BoolList::compress()
{
    int empty = 0;
    for (int i = 0; i < blocks; i++)
    {
        if (vec[i] != 0)
            break;
        else
            empty++;
    }
    if (empty != 0)
    {
        if (empty == blocks)
        {
            delete[] vec;
            vec = new ull[1];
            blocks = 1;
        }
        else
        {
            ull* tmp = new ull[blocks - empty];
            for (int i = blocks - 1; i > empty - 1; i--)
                tmp[blocks - 1 - i] = vec[i];
            delete[] vec;
            vec = new ull[blocks - empty];
            for (int i = 0; i < blocks - empty; i++)
                vec[i] = tmp[i];
            blocks = blocks - empty;

            delete[] tmp;
        }
    }
}

void BoolList::stretch(unsigned int s_blocks)
{
    ull* tmp = new ull[s_blocks];
    if (s_blocks == blocks)
        return;
    int vec_j = 0;

    for (int i = s_blocks - 1; i >= 0; i--)
    {
        if (vec_j < blocks)
        {
            tmp[i] = vec[blocks - 1 - vec_j];
            vec_j++;
        }
        else
        {
            tmp[i] = 0;    
        }
    }
    delete[] vec;
    vec = new ull[s_blocks];
    for (int i = 0; i < s_blocks; i++)
        vec[i] = tmp[i];
    delete[] tmp;
    blocks = s_blocks;
}


void BoolList::clear()
{
    delete[] vec;
    for (int i = 0; i < blocks; i++)
        vec[i] = 0;

}
