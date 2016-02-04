#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <set>
#include <iterator>
#include <queue>
using namespace std;
int main(void)
{
    int n, e, c1, c2;
    cin >> n >> e;
    vector< vector<int> > v(n);
    for(size_t i = 0; i < e; i++)
    {
        cin >> c1 >> c2;
        v[c2].push_back(c1);
        v[c1].push_back(c2);
    }
    vector<bool> en(n + 1, false);
    vector<int> color(n + 1, 0);
    color[n] = 0;
    int iter = 0;
    stack<int> q;

    while(iter < n)
    {

        color[iter] = 1;
        q.push(iter);

        while(!q.empty())
        {
           // copy(color.begin(), color.end(), ostream_iterator<int>(cout, " ")); cout << endl;

            int cur = q.top();
            q.pop();
            if(!en[cur])
            {
                for(size_t i = 0; i < v[cur].size(); i++)
                {
                    if(color[v[cur][i]] == color[cur])
                    {
                        cout << "NO" << endl;
                        return 0;
                    }
                    if(color[cur] == 1)
                    {
                        color[v[cur][i]] = 2;
                        q.push(v[cur][i]);
                    }
                    if(color[cur] == 2)
                    {
                        color[v[cur][i]] = 1;
                        q.push(v[cur][i]);
                    }
                }
                en[cur] = true;
            }

        }
        while(en[iter])
        {
            iter++;
        }
    }
    cout << "YES" << endl;
    for(size_t i = 0; i < n; i++)
    {
        if(color[i] == 1) cout << i << " ";
    }
    return 0;
}