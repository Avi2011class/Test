#include <locale.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include <stack>
using namespace std;


vector <int> G[100010];
vector <int> Gt[100010]; // транспонированній граф
vector<bool> used;
vector<int> order, component;
int res[100010];
int n, m, num = 0;

void dfs_1 (int u)
{
    used[u]=1;
    for (int i=0; i<G[u].size(); i++)
    {
        if (used[G[u][i]]==0)
        {
            dfs_1(G[u][i]);
        }
    }
    order.push_back(u);
}

void dfs_2 (int u)
{
    used[u]=1;
    component.push_back(u);
    for (int i=0; i<Gt[u].size(); i++)
    {
        if (used[Gt[u][i]]==0)
        {
            dfs_2 (Gt[u][i]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        Gt[b].push_back(a);
    }

    used.assign (n, false);

    for (int i=0; i<n; i++)
    {
        if (used[i]==0) dfs_1(i);
    }

    used.assign (n, false);

    for (int i=0; i<n; i++)
    {
        int v=order[n-1-i];
        if (used[v]==0)
        {
            dfs_2 (v);
            for(vector<int>::iterator I=component.begin(); I!=component.end(); I++)
                res[*I]=num;
            num++;
            component.clear();
        }
    }

    vector<int> example(num, -1);


    for (int i = 0; i < n; i++)
    {
        if(example[res[i]] == -1) example[res[i]] = i;
    }

    vector<bool> endf(n, false);
    int iter = 0;
    stack<int> st;
    int answer = 0;

    while(iter < num)
    {


        int cur = example[iter];
        if( !endf[cur] )
        {
            st.push(cur);
            endf[cur] = true;
            while(!st.empty())
            {
                cur = st.top();
                st.pop();
                for(int i = 0; i < G[cur].size(); i++)
                if(!endf[G[cur][i]])
                {
                    st.push(G[cur][i]);
                    endf[G[cur][i]] = true;
                }
            }
            answer++;
        }
        iter++;

    }
    cout << answer;



    return 0;
}