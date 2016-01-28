#include <stdio.h>
#include <stdlib.h>


/*
Система непересекающихся множеств
В данной статье рассматривается структура данных "система непересекающихся множеств" 
(на английском "disjoint-set-union", или просто "DSU").

Эта структура данных предоставляет следующие возможности.'
' Изначально имеется несколько элементов, каждый из которых находится в отдельном 
(своём собственном) множестве. За одну операцию можно объединить два каких-либо множества,
 а также можно запросить, в каком множестве сейчас находится указанный элемент. 
 Также, в классическом варианте, вводится ещё одна операция — создание нового элемента, 
 который помещается в отдельное множество.

Таким образом, базовый интерфейс данной структуры данных состоит всего из трёх операций:

{\rm make\_set}(x) — добавляет новый элемент x, помещая его в новое множество, состоящее из одного него.
{\rm union\_sets}(x,y) — объединяет два указанных множества 
(множество, в котором находится элемент x, и множество, в котором находится элемент y).
{\rm find\_set}(x) — возвращает, в каком множестве находится указанный элемент x.
 На самом деле при этом возвращается один из элементов множества (называемый представителем 
 или лидером (в англоязычной литературе "leader")). Этот представитель выбирается в
 каждом множестве самой структурой данных (и может меняться с течением времени, а именно,
 после вызовов {\rm union\_sets}()).
*/


/*---------------DSU--------------------------*/
struct DSU
{
    int* Parent;
    int* Range;
    int Length;
};
struct DSU* DSUInit(int Count);
void DSUMakeNewSet(struct DSU* D, int V);
int DSUFindSet(struct DSU* D, int V);
void DSUUnionSets(struct DSU* D, int X, int Y);
/*---------------------------------------------*/
struct DSU* DSUInit(int Count)
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
void DSUMakeNewSet(struct DSU* D, int V)
{
    D->Parent[V] = V;
    D->Range[V] = 1;
}
int DSUFindSet(struct DSU* D, int V)
{
    if(D->Parent[V] == V)
        return V;
    else
    {
        D->Parent[V] = DSUFindSet(D, D->Parent[V]);
        return D->Parent[V];
    }

}
void DSUUnionSets(struct DSU* D, int X, int Y)
{
    X = DSUFindSet(D, X);
	Y = DSUFindSet(D, Y);
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
int main(void)
{
    return 0;
}
