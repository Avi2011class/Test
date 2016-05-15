#include <iostream>
#include <vector>
#include <iterator>
#include <cstdio>
#include <stack>
#include <set>

using namespace std;

void DfsOrder(vector< vector<int> > &Graph, int Current, vector<bool> &Used, vector<int> &Order)
{
    Used[Current] = true;
    for(size_t i = 0; i < Graph[Current].size(); i++)
        if(!Used[Graph[Current][i]])
            DfsOrder(Graph, Graph[Current][i], Used, Order);
    Order.push_back(Current);
}
void DfsComponent(vector< vector<int> > &GraphTranspose,
                  int Current, vector<bool> &Used, vector<int> &Color, int CurColor)
{
    Used[Current] = true;
    Color[Current] = CurColor;
    for(size_t i = 0; i < GraphTranspose[Current].size(); i++)
        if(!Used[GraphTranspose[Current][i]])
            DfsComponent(GraphTranspose, GraphTranspose[Current][i], Used, Color, CurColor);
}
int main(void)
{
    //freopen("input.txt", "r", stdin);
    int V, E;
    cin >> V >> E;
    vector< vector<int> > Graph(V), GraphTranspose(V);

    int BeginV, EndV;
    for(size_t i = 0; i < E; i++)
    {
        cin >> BeginV >> EndV;
        Graph[BeginV - 1].push_back(EndV - 1);
        GraphTranspose[EndV - 1].push_back(BeginV - 1);
    }

    vector<int> Order;
    Order.reserve(V);
    vector<bool> Used(V + 1);

    for(size_t i = 0; i < V; i++)
        if(!Used[i])
            DfsOrder(Graph, i, Used, Order);
    Used.assign(V, false);

    vector<int> Color(V);
    int CurColor = 0;
    for(size_t i = 0; i < V; i++)
    {
        int Current = Order[V - i - 1];
        if(!Used[Current])
            {
                DfsComponent(GraphTranspose, Current, Used, Color, CurColor);
                CurColor++;
            }
    }

    //copy(Color.begin(), Color.end(), ostream_iterator<int>(cout, " "));
    //cout << endl;

    set<int> Result;
    for(size_t i = 0; i < GraphTranspose.size(); i++)
        for(size_t j = 0; j < GraphTranspose[i].size(); j++)
            if(Color[i] != Color[GraphTranspose[i][j]])
                Result.insert(Color[i]);

    //copy(GetInput.begin(), GetInput.end(), ostream_iterator<int>(cout, " "));
    //cout << endl;

    cout << CurColor - Result.size() << endl;
    return 0;
}
