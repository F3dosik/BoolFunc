#ifndef BOOLLIST_H
#define BOOLLIST_H

#include "common.h"
#include <string>

typedef unsigned long long ull;

class BoolList
{
public:

    unsigned int blocks;
    ull* vec;

    
    BoolList(unsigned int len);
    BoolList(std::string line);
    BoolList(BoolList& bl);
    BoolList(const BoolList* bl);
    unsigned int wht() { return weight(vec, blocks); }

    bool operator [](unsigned int i);
    void operator =(BoolList bl);
    //void operator =(BoolList& bl);
    BoolList operator<< (unsigned int i) const;
    BoolList operator>> (unsigned int i) const;
    //const BoolList operator& (BoolList& bl) const;
    BoolList operator| (BoolList bl) const;
    BoolList operator& (BoolList bl) const;
    //BoolList operator| (const BoolList bl) const;

    void show_list();
    void compress();
    void stretch(unsigned int s_blocks);
    void clear();
    ~BoolList() { delete[] vec; }
};

#endif
