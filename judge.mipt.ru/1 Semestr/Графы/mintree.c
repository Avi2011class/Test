#include <stdio.h>
#include <stdlib.h>

/*---------------DSU--------------------------*/
struct DSU
{
    int* Parent;
    int* Range;
    int Length;
};
struct DSU* Init(int Count);
void MakeNewSet(struct DSU* D, int V);
int FindSet(struct DSU* D, int V);
void UnionSets(struct DSU* D, int X, int Y);
/*---------------------------------------------*/
struct DSU* Init(int Count)
{
    struct DSU* D = (struct DSU*)malloc(sizeof(struct DSU));
    D->Parent = (int*)malloc(Count * sizeof(int));
    D->Range = (int*)malloc(Count * sizeof(int));

    int i = 0;
    for(i = 0; i < Count; i++)
    {
        D->Parent[i] = -1;
        D->Range[i] = 0;
    }
    D->Length = Count;
    return D;
}
void MakeNewSet(struct DSU* D, int V)
{
    D->Parent[V] = V;
    D->Range[V] = 1;
}
int FindSet(struct DSU* D, int V)
{
    if(D->Parent[V] == V)
        return V;
    else
    {
        D->Parent[V] = FindSet(D, D->Parent[V]);
        return D->Parent[V];
    }

}
void UnionSets(struct DSU* D, int X, int Y)
{
    X = FindSet(D, X);
	Y = FindSet(D, Y);
	if (X != Y)
    {
        if (D->Range[X] < D->Range[Y])
        {
            int Buf = X;
            X = Y;
            Y = Buf;
        }
		D->Parent[Y] = X;
		D->Range[X] += D->Range[Y];
    }
}
/*---------------------------------------------*/

struct edge
{
    int first;
    int second;
    int length;
};

int cmp_edge(const void* a, const void* b)
{
    return ((struct edge*)a)->length - ((struct edge*)b)->length;
}


int main(void)
{
    int N, M, i;
    scanf("%d %d", &N, &M);
    struct edge* E = (struct edge*)malloc(sizeof(struct edge) * M);
    for(i = 0; i < M; i++)
        scanf("%d %d %d", &(E[i].first), &(E[i].second), &(E[i].length));
    qsort(E, M, sizeof(struct edge), cmp_edge);

    struct DSU* D = Init(N);
    for(i = 0; i < N; i++)
        MakeNewSet(D, i);
    int res = 0;
    for(i = 0; i < M; i++)
    {
        if(FindSet(D, E[i].first) != FindSet(D, E[i].second))
        {
            res += E[i].length;
            UnionSets(D, E[i].first, E[i].second);
        }
    }
    printf("%d", res);
    return 0;
}