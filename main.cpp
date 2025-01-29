#include <iostream>
#include <climits>
#include "BoolList.h"

using namespace std;

typedef unsigned long long ull;

int main()
{
    string line = "11111111100011110000000000000000000000000000000000000000000000000000000000101";
    BoolList bl(line);
    bl.show_list();

    bl = bl << 127;

    bl.show_list();

    bl = bl >> 127;
    bl.show_list();
    return 0;

}
