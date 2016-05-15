#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main(void)
{
    unsigned int a, b;
    cin >> hex >> a >> b;
    cout << hex << (a^b);
    return (a^b);
}
