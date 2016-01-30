/*
Декартово дерево (tree + heap -> treap) — красивая и легко
реализующаяся структура данных, которая с минимальными
усилиями позволит вам производить многие скоростные
операции над массивами данных.
http://habrahabr.ru/post/101818/
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct TreapNode
{
    int Key;
    int Priority;
    struct TreapNode* Left;
    struct TreapNode* Right;
};
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
struct TreapNode* TreapMerge(struct TreapNode* First, struct TreapNode* Second)
{
    if(First == NULL)
        return Second;
    if(Second == NULL)
        return First;
    if(First->Priority > Second->Priority)
    {
        struct TreapNode* Result = (struct TreapNode*)malloc(sizeof(struct TreapNode));
        if(Result == NULL)
            return NULL;
        Result->Key = First->Key;
        Result->Priority = First->Priority;
        Result->Left = First->Left;
        Result->Right = TreapMerge(First->Right, Second);
        free(First);
        return Result;
    }
    if(First->Priority <= Second->Priority)
    {
        struct TreapNode* Result = (struct TreapNode*)malloc(sizeof(struct TreapNode));
        if(Result == NULL)
            return NULL;
        Result->Key = Second->Key;
        Result->Priority = Second->Priority;
        Result->Left = TreapMerge(First, Second->Left);
        Result->Right = Second->Right;
        return Result;
    }
    return NULL;
}

void TreapSplit(struct TreapNode* Treap, int SplitKey, struct TreapNode** L, struct TreapNode** R)
{
    struct TreapNode* NewTree = NULL;
    if(Treap->Key <= SplitKey)
    {
        if(Treap->Right == NULL)
            *R = NULL;
        else
            TreapSplit(Treap->Right, SplitKey, &NewTree, R);
        *L = (struct TreapNode*)malloc(sizeof(struct TreapNode));
        (*L)->Key = Treap->Key;
        (*L)->Priority = Treap->Priority;
        (*L)->Left = Treap->Left;
        (*L)->Right = NewTree;
    }
    else
    {
        if(Treap->Left == NULL)
            *L = NULL;
        else
            TreapSplit(Treap->Left, SplitKey, L, &NewTree);
        *R = (struct TreapNode*)malloc(sizeof(struct TreapNode));
        (*R)->Key = Treap->Key;
        (*R)->Priority = Treap->Priority;
        (*R)->Left = NewTree;
        (*R)->Right = Treap->Right;
    }
}
void TreapPrint(struct TreapNode* Treap, int Tab)
{
    int i;
    if(Treap->Left != NULL)
        TreapPrint(Treap->Left, Tab + 1);
    for(i = 0; i < Tab - 1; i++)
        printf("   |");
    if(Tab != 0)
        printf("   ");
    printf("(%d, %d)\n", Treap->Key, Treap->Priority);
    if(Treap->Right != NULL)
        TreapPrint(Treap->Right, Tab + 1);
}

int main(void)
{
    srand(time(0));
    int i;
    struct TreapNode* arr[10];
    for(i = 0; i < 10; i++)
    {
        arr[i] = (struct TreapNode*)malloc(sizeof(struct TreapNode));
        arr[i]->Key = rand() % 50;
        arr[i]->Priority =  rand() % 50;
        arr[i]->Left = NULL;
        arr[i]->Right = NULL;
    }
    struct TreapNode* T = NULL;
    for(i = 0; i < 10; i++)
    {
        T = TreapMerge(T, arr[i]);
        TreapPrint(T, 0);
        printf("------------------------------------\n");
    }

    for(i = 0; i < 10; i++)
    {
        free(arr[i]);
    }
    return 0;
}
