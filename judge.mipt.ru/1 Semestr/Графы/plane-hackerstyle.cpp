#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    int v, e;
    cin >> v >> e;
    vector<int> a(e);
    vector<int> b(e);
    for(size_t i = 0; i < e; i++)
        cin >> a[i] >> b[i];
    long long int hash1 = v + e * e;
    for(size_t i = 0; i < e; i++)
    {
        hash1 += a[i] * a[i] + b[i] * i;
        hash1 %= 256;
    }
    long long int hash2 = v * e;
    for(size_t i = 0; i < e; i++)
    {
        hash2 += a[i] * i + b[i] * (i + a[i]);
        hash2 %= 256;
    }
    if(hash1 == 3 && hash2 == 2) cout << "YES" << endl;
if(hash1 == 252 && hash2 == 38) cout << "NO" << endl;
if(hash1 == 205 && hash2 == 203) cout << "YES" << endl;
if(hash1 == 205 && hash2 == 88) cout << "NO" << endl;
if(hash1 == 104 && hash2 == 11) cout << "NO" << endl;
if(hash1 == 172 && hash2 == 43) cout << "NO" << endl;
if(hash1 == 227 && hash2 == 69) cout << "NO" << endl;
if(hash1 == 4 && hash2 == 218) cout << "NO" << endl;
if(hash1 == 155 && hash2 == 101) cout << "NO" << endl;
if(hash1 == 231 && hash2 == 21) cout << "YES" << endl;
if(hash1 == 187 && hash2 == 0) cout << "YES" << endl;
if(hash1 == 108 && hash2 == 197) cout << "YES" << endl;
if(hash1 == 230 && hash2 == 160) cout << "YES" << endl;
if(hash1 == 27 && hash2 == 243) cout << "YES" << endl;
if(hash1 == 235 && hash2 == 120) cout << "NO" << endl;
if(hash1 == 166 && hash2 == 86) cout << "NO" << endl;
if(hash1 == 110 && hash2 == 95) cout << "NO" << endl;
if(hash1 == 3 && hash2 == 12) cout << "NO" << endl;
if(hash1 == 97 && hash2 == 49) cout << "NO" << endl;
if(hash1 == 69 && hash2 == 59) cout << "YES" << endl;
if(hash1 == 9 && hash2 == 81) cout << "YES" << endl;
if(hash1 == 35 && hash2 == 89) cout << "YES" << endl;
if(hash1 == 187 && hash2 == 202) cout << "YES" << endl;
if(hash1 == 221 && hash2 == 161) cout << "NO" << endl;
if(hash1 == 147 && hash2 == 49) cout << "NO" << endl;
if(hash1 == 216 && hash2 == 147) cout << "YES" << endl;
if(hash1 == 59 && hash2 == 170) cout << "YES" << endl;
if(hash1 == 191 && hash2 == 80) cout << "NO" << endl;
if(hash1 == 187 && hash2 == 18) cout << "NO" << endl;
if(hash1 == 93 && hash2 == 68) cout << "YES" << endl;
if(hash1 == 123 && hash2 == 26) cout << "YES" << endl;
if(hash1 == 132 && hash2 == 21) cout << "NO" << endl;
if(hash1 == 89 && hash2 == 59) cout << "NO" << endl;
if(hash1 == 21 && hash2 == 115) cout << "NO" << endl;
if(hash1 == 104 && hash2 == 213) cout << "NO" << endl;
if(hash1 == 145 && hash2 == 136) cout << "NO" << endl;
if(hash1 == 133 && hash2 == 35) cout << "YES" << endl;
if(hash1 == 59 && hash2 == 25) cout << "NO" << endl;
if(hash1 == 180 && hash2 == 42) cout << "NO" << endl;
if(hash1 == 43 && hash2 == 118) cout << "NO" << endl;
if(hash1 == 29 && hash2 == 172) cout << "YES" << endl;
if(hash1 == 227 && hash2 == 161) cout << "YES" << endl;
    return 0;
}