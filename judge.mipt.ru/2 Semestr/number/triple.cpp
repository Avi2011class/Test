#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    string a;
    cin >> a;
    long long int res = 0;
    string::iterator it = a.end();
    long long int mod = 1;
    while(1)
    {
        it--;
        res += (*it - '0') * mod;
        mod *= 3;
        if(it == a.begin())
            break;
    }
    cout << res;
    return 0;
}