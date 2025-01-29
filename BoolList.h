#ifndef BOOLLIST_H
#define BOOLLIST_H

#include "common.h"
#include <string>

typedef unsigned long long ull;

class BoolList
{
public:

    unsigned int length;
    unsigned int blocks;
    ull* vec;

    
    BoolList(unsigned int len);
    BoolList(std::string line);
    BoolList(BoolList& bl);
    unsigned int wht() { return weight(vec, blocks); }

    bool operator [](unsigned int i);
    void operator =(const BoolList bl);
    void operator =(BoolList& bl);
    const BoolList operator <<(unsigned int i);
    const BoolList operator >>(unsigned int i);
    void operator &(BoolList& bl);
    void operator |(BoolList& bl);

    void show_list();

    ~BoolList() { delete[] vec; }
};

#endif
