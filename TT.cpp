#include "TT.h"
typedef unsigned long long ull;

TT::TT(ull vars) : n(vars)
{
    TT::vec = new ull[n];
    for (int i = 0; i < n; i++)
        vec[i] = 0;
}
    TT::TT(){}

