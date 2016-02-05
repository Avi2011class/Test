#include <iostream>
#include <vector>
#include <iterator>


using namespace std;

struct tr
{
    int first;
    int second;
    int len;
};
int main(int argc, char** argv)
{
    int V, E;
    cin >> V >> E;
    vector<tr> p(E);
    for(size_t i = 0; i < E; i++)
        cin >> p[i].first >> p[i].second >> p[i].len;
    int start;
    cin >> start;
    vector<int> res(V, 1000000);
    res[start] = 0;
    bool flag = true;
    while(flag)
    {
        flag = false;
        for(size_t i = 0; i < E; i++)
        {
            if(res[p[i].second] > res[p[i].first] + p[i].len)
            {
                flag = true;
                res[p[i].second] = res[p[i].first] + p[i].len;
            }
            if(res[p[i].first] > res[p[i].second] + p[i].len)
            {
                flag = true;
                res[p[i].first] = res[p[i].second] + p[i].len;
            }
        }
    }
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
    return 0;
}