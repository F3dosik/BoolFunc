#ifndef BOOLLIST_H
#define BOOLLIST_H

#include "common.h"
#include <string>

typedef unsigned long long ull;

class BoolList
{
    unsigned int length;
    unsigned int blocks;
    ull* vec;

public:
    
    BoolList(unsigned int len);
    BoolList(std::string line);
    BoolList(BoolList& bl);
    
    bool operator [](unsigned int i);
    void operator <<(unsigned int i);
    void operator >>(unsigned int i);
    void operator &(BoolList& bl);
    void operator |(BoolList& bl);

    void show_list();

    ~BoolList() { delete[] vec; }
};

#endif
