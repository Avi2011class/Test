#include <limits>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
int main()
{
    int si = 0;
    string type;
    getline(cin, type);
    if (type == "float")
    {
        si = std::numeric_limits<float>::digits;
    }
    else
        if (type == "double")
        {
            si = std::numeric_limits<double>::digits;
        }
        else
            if (type == "long double")
            {
                si = std::numeric_limits<long double>::digits;
            }

    printf ("%d\n", si - 1);
}
