#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;
int get_num(char ch)
{
    if(ch >= '0' && ch <='9')
        return ch - 48;
    if(ch >= 'A' && ch <= 'Z')
        return ch - 'A' + 10;
    return -1;
}
char set_ch(int x)
{
    string s = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return s[x];
}
int main()
{
    int is, os;
    string s;
    cin >> is >> s >> os;
    vector<int> v(s.length());
    for(size_t i = 0; i < s.length(); i++)
        v[i] = get_num(s[i]);

    reverse(v.begin(), v.end());

    long long int x = 0;
    long long int mod = 1;
    for(int i = 0; i < v.size(); i++)
    {
        x += v[i] * mod;
        mod *= is;
    }
    if(x == 0)
    {
        cout << x;
        return 0;
    }
    vector<int> result;
    while(x)
    {
        result.push_back(x % os);
        x = x / os;
    }

    for(int i = result.size()-1; i >=0 ; i--)
        cout << set_ch(result[i]);
    cout << endl;
    return 0;
}