#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <set>
#include <iterator>
#include <queue>
#include <string>
#include <map>
using namespace std;
int main(void)
{
        int n, e, v1, v2, r;
    cin >> n >> e;
    vector< vector< pair<int, int> > > v(n);
    for(size_t i = 0; i < e; i++)
    {
        cin >> v1 >> v2 >> r;
        v[v1].push_back(make_pair(v2, r));
        v[v2].push_back(make_pair(v1, r));
    }
    int start;
    cin >> start;
    vector<int> en(n, false);
    vector<int> ro(n, 1000000000);
    ro[start] = 0;
    en[start] = true;

    while(true)
    {
        for(size_t i = 0; i < n; i++)
            if(en[i])
            {
                for(size_t j = 0; j < v[i].size(); j++)
                    if(ro[v[i][j].first] > ro[i] + v[i][j].second)
                    {
                        ro[v[i][j].first] = ro[i] + v[i][j].second;
                        en[v[i][j].first] = true;
                    }
                en[i] = false;
            }
        bool b = false;
        for(size_t i = 0; i < n; i++) b = b || en[i];
        if(!b) break;
    }
    for(size_t i = 0; i < n; i++)
        cout << ro[i] << " ";
    return 0;
}