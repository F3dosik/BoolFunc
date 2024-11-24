#ifndef TT_H
#define TT_H

typedef unsigned long long ull;

class TT
{
    ull* vec;
    ull n;
public:

    TT();
    TT(ull vars); //only vars - null function
    TT(ull func);  //<= 6 vars
    TT(std::string func); //bipki
    ull* get_vec() { return vec; }
};


#endif
