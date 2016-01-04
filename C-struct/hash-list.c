#include <stdio.h>
#include <stdlib.h>
struct node {
    int Key;
    int Next;
    struct node *Left;
    struct node *Right;
    unsigned char Height;
};
unsigned char Height(struct node *P);
int BalanceFactor(struct node *P);
struct node *FindMin(struct node *P);
struct node *RemoveMin(struct node *P);
void FixHeight(struct node *P);
struct node *RotateRight(struct node *P);
struct node *RotateLeft(struct node *P);
struct node *Balance(struct node *P);
struct node *Insert(struct node *P, int K);
struct node *Remove(struct node *P, int K);
struct node *Search(struct node *P, int Val);
unsigned char Height(struct node *P)
{
    return P ? P->Height : 0;
}

int BalanceFactor(struct node *P)
{
    return Height(P->Right) - Height(P->Left);
}

struct node *FindMin(struct node *P)
{
    return (P->Left != NULL) ? FindMin(P->Left) : P;
}

struct node *RemoveMin(struct node *P)
{
    if (P->Left == 0)
        return P->Right;
    P->Left = RemoveMin(P->Left);
    return Balance(P);
}

void FixHeight(struct node *P)
{
    unsigned char HL = Height(P->Left);
    unsigned char HR = Height(P->Right);
    P->Height = ((HL > HR) ? HL : HR) + 1;
}

struct node *RotateRight(struct node *P)
{
    struct node *Q = P->Left;
    P->Left = Q->Right;
    Q->Right = P;
    FixHeight(P);
    FixHeight(Q);
    return Q;
}

struct node *RotateLeft(struct node *P)
{
    struct node *Q = P->Right;
    P->Right = Q->Left;
    Q->Left = P;
    FixHeight(P);
    FixHeight(Q);
    return Q;
}

struct node *Balance(struct node *P)
{
    FixHeight(P);
    if (BalanceFactor(P) == 2) {
        if (BalanceFactor(P->Right) < 0)
            P->Right = RotateRight(P->Right);
        return RotateLeft(P);
    }
    if (BalanceFactor(P) == -2) {
        if (BalanceFactor(P->Left) > 0)
            P->Left = RotateLeft(P->Left);
        return RotateRight(P);
    }
    return P;
}

struct node *Insert(struct node *P, int K)
{
    if (!P) {
        struct node *Newnode =
            (struct node *)calloc(sizeof(struct node),
                      1);
        Newnode->Key = K;
        Newnode->Next = -1;
        return Newnode;
    }
    if (K < P->Key)
        P->Left = Insert(P->Left, K);
    else
        P->Right = Insert(P->Right, K);
    return Balance(P);
}

struct node *Remove(struct node *P, int K)
{
    if (!P)
        return 0;
    if (K < P->Key)
        P->Left = Remove(P->Left, K);
    else if (K > P->Key)
        P->Right = Remove(P->Right, K);
    else {
        struct node *Q = P->Left;
        struct node *R = P->Right;
        free(P);
        if (!R)
            return Q;
        struct node *Min = FindMin(R);
        Min->Right = RemoveMin(R);
        Min->Left = Q;
        return Balance(Min);
    }
    return Balance(P);
}

void Print(struct node *P, int Tab)
{
    int i;
    if (P != NULL) {
        for (i = 0; i < Tab; i++)
            printf("|   ");
        printf("%d\n", P->Key);
        Print(P->Left, Tab + 1);
        Print(P->Right, Tab + 1);
    }
}

struct node *Search(struct node *P, int Val)
{
    if (P == NULL)
        return NULL;
    if (P->Key == Val)
        return P;
    if (P->Key > Val)
        return Search(P->Left, Val);
    if (P->Key < Val)
        return Search(P->Right, Val);
    return NULL;
}

int main(void)
{
    int t, prev;
    struct node *P = NULL;
    scanf("%d", &t);
    prev = t;
    while (scanf("%d", &t) != 0) {
        struct node *Pr = Search(P, prev);
        if (Pr != NULL)
            Pr->Next = t;
        prev = t;
        if (Search(P, t) == NULL)
            P = Insert(P, t);
    }
    struct node *Pr = Search(P, t);
    printf("%d\n", Pr->Next);
    return 0;
}
