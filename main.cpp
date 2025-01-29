#include <iostream>
#include <climits>
#include "BoolList.h"

using namespace std;

typedef unsigned long long ull;

int main()
{
    string line = "11111111100011000000000000000000000000000000000000000000000000000000000000101";
    BoolList bl(line);
    bl.show_list();


    for (int i = 127; i >= 0; i--)
    {
        cout << bl[i];
    }
    cout << endl;

    return 0;

}
