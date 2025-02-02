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
    
    BoolList bl2("110");
    bl2.stretch(2);
    bl2 = bl2 << 60;
    bl2.show_list(); 

    bl1 = bl1 & bl2;
    bl1.show_list();

    return 0;

}
