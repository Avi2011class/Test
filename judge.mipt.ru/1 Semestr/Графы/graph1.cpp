#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
int main(void)
{
    int count = 0;
    int n;
    int c;
    cin >> n;
    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < n; j++)
        {
            cin >> c;
            if(c) count++;
        }
    cout << count / 2 << endl;
    return 0;
}