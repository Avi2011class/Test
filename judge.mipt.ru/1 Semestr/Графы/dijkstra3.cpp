#include <stdio.h>
#include <stdlib.h>
struct edge { int first; int second; int len; };
int main(int argc, char** argv)
{
    int V, E, i; scanf("%d%d", &V, &E);
    struct edge* p = (struct edge*)malloc(sizeof(struct edge) * E);
    for(i = 0; i < E; i++)
        scanf("%d%d%d", &p[i].first, &p[i].second, &p[i].len);
    int start; scanf("%d", &start);
    int* res = (int*)malloc(sizeof(int) * V);
    for(i = 0; i < V; i++) res[i] = 10000000;
    res[start] = 0;
    int flag = 1;
    while(flag)
    {
        flag = 0;
        for(i = 0; i < E; i++)
            if(res[p[i].second] > res[p[i].first] + p[i].len)
            {
                flag = 1;
                res[p[i].second] = res[p[i].first] + p[i].len;
            }
            else if(res[p[i].first] > res[p[i].second] + p[i].len)
            {
                flag = 1;
                res[p[i].first] = res[p[i].second] + p[i].len;
            }
    }
    for(i = 0; i < V; i++) printf("%d ", res[i]);
    free(p);
    free(res);
    return 0;
}