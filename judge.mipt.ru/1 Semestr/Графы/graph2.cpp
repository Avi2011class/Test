#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;
int main(void)
{
    vector< vector<int> > v;
    int n, e, c1, c2;
    cin >> n >> e;
    v.resize(n);
    for(size_t i = 0; i < n; i++) v[i].resize(n);
    for(size_t i = 0; i < e; i++)
    {
        cin >> c1 >> c2;
        v[c1][c2] = 1;
        v[c2][c1] = 1;
    }
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}