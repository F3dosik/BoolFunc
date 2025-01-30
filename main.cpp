#include <iostream>
#include <climits>
#include "BoolList.h"

using namespace std;

typedef unsigned long long ull;

int main()
{
    string line = "11111111100011110000000000000000000000000000000000000000000000000000000000101";
    BoolList bl1(line);
    bl1.show_list();
    
    BoolList bl2("100");
    bl1 = bl1 << 50;
    bl1.vec[0] = 0;
    
    bl1.compress();
    
    bl1.show_list();

    bl1.stretch(2);

    bl1.show_list();

    bl1.stretch(1);

    bl1.show_list();
    return 0;

}
