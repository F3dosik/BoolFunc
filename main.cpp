#include <iostream>
#include <climits>
#include "BoolList.h"

using namespace std;

typedef unsigned long long ull;

double sum = 0;
int blocks;
int end;

int main()
{
    int vars;

    cin >> vars;

    BoolList bl(1 << vars);

    blocks = bl.blocks;
    
    ull end = 1 << vars;
    bl.vec[blocks - 1] += 1;
    int wht = 1;
    double all = 1;
    all /= (1 << (1 << vars));
    cout << all << endl;
    sum += 1 * all;
    ull temp;
    while (wht != end)
    {
        temp = bl.vec[blocks - 1];
        bl.vec[blocks - 1]++;
        if (temp > bl.vec[blocks - 1])
        {
            int i = blocks - 2;
            while (i >= 0)
            {
                temp = bl.vec[i];
                bl.vec[i]++;
                if (temp > bl.vec[i])
                    i--;
                else
                    break;
            }
        }
        wht = bl.wht();
        sum += wht * all;
    }
    std::cout << sum << endl;
    return 0;
}
