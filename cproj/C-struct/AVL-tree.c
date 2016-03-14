#include <stdio.h>
#include <stdlib.h>

/*---------------AVL_TREE----------------------*/
struct AVL_TREE_Node
{
    int Key;
    struct AVL_TREE_Node* Left;
    struct AVL_TREE_Node* Right;
    unsigned char AVL_TREE_Height;
};
unsigned char           AVL_TREE_Height         (struct AVL_TREE_Node* P);
int                     AVL_TREE_BalanceFactor  (struct AVL_TREE_Node* P);
struct AVL_TREE_Node*   AVL_TREE_FindMin        (struct AVL_TREE_Node* P);
struct AVL_TREE_Node*   AVL_TREE_RemoveMin      (struct AVL_TREE_Node* P);
void                    AVL_TREE_FixHeight      (struct AVL_TREE_Node* P);
struct AVL_TREE_Node*   AVL_TREE_RotateRight    (struct AVL_TREE_Node* P);
struct AVL_TREE_Node*   AVL_TREE_RotateLeft     (struct AVL_TREE_Node* P);
struct AVL_TREE_Node*   AVL_TREE_Balance        (struct AVL_TREE_Node* P);

struct AVL_TREE_Node*   AVL_TREE_Insert         (struct AVL_TREE_Node* P, int K);
struct AVL_TREE_Node*   AVL_TREE_Remove         (struct AVL_TREE_Node* P, int K);
void                    AVL_TREE_Print          (struct AVL_TREE_Node* P, int Tab);
struct AVL_TREE_Node*   AVL_TREE_Find           (struct AVL_TREE_Node* P, int K);
void                    AVL_TREE_Destroy        (struct AVL_TREE_Node* P);
/*---------------------------------------------*/

unsigned char AVL_TREE_Height(struct AVL_TREE_Node* P)
{
	return P ? P->AVL_TREE_Height : 0;
}
int AVL_TREE_BalanceFactor(struct AVL_TREE_Node* P)
{
	return AVL_TREE_Height(P->Right) - AVL_TREE_Height(P->Left);
}
struct AVL_TREE_Node* AVL_TREE_FindMin(struct AVL_TREE_Node* P)
{
	return (P->Left != NULL) ? AVL_TREE_FindMin(P->Left) : P;
}
struct AVL_TREE_Node* AVL_TREE_RemoveMin(struct AVL_TREE_Node* P)
{
	if( P->Left == 0 )
		return P->Right;
	P->Left = AVL_TREE_RemoveMin(P->Left);
	return AVL_TREE_Balance(P);
}
void AVL_TREE_FixHeight(struct AVL_TREE_Node* P)
{
    unsigned char HL = AVL_TREE_Height(P->Left);
    unsigned char HR = AVL_TREE_Height(P->Right);
    P->AVL_TREE_Height = ((HL > HR) ? HL : HR) + 1;
}
struct AVL_TREE_Node* AVL_TREE_RotateRight(struct AVL_TREE_Node* P)
{
    struct AVL_TREE_Node* Q = P->Left;
	P->Left = Q->Right;
	Q->Right = P;
	AVL_TREE_FixHeight(P);
	AVL_TREE_FixHeight(Q);
	return Q;
};
struct AVL_TREE_Node* AVL_TREE_RotateLeft(struct AVL_TREE_Node* P)
{
    struct AVL_TREE_Node* Q = P->Right;
	P->Right = Q->Left;
	Q->Left = P;
	AVL_TREE_FixHeight(P);
	AVL_TREE_FixHeight(Q);
	return Q;
};
struct AVL_TREE_Node* AVL_TREE_Balance(struct AVL_TREE_Node* P)
{
	AVL_TREE_FixHeight(P);
	if( AVL_TREE_BalanceFactor(P) == 2 )
	{
		if( AVL_TREE_BalanceFactor(P->Right) < 0 )
			P->Right = AVL_TREE_RotateRight(P->Right);
		return AVL_TREE_RotateLeft(P);
	}
	if( AVL_TREE_BalanceFactor(P) == -2 )
	{
		if( AVL_TREE_BalanceFactor(P->Left) > 0  )
			P->Left = AVL_TREE_RotateLeft(P->Left);
		return AVL_TREE_RotateRight(P);
	}
	return P;
}
struct AVL_TREE_Node* AVL_TREE_Insert(struct AVL_TREE_Node* P, int K)
{
	if( !P )
    {
        struct AVL_TREE_Node* NewNode = (struct AVL_TREE_Node*)calloc(sizeof(struct AVL_TREE_Node), 1);
        NewNode->Key = K;
        return NewNode;
    }
	if( K < P->Key )
		P->Left = AVL_TREE_Insert(P->Left, K);
	else
		P->Right = AVL_TREE_Insert(P->Right, K);
	return AVL_TREE_Balance(P);
}
struct AVL_TREE_Node* AVL_TREE_Remove(struct AVL_TREE_Node* P, int K)
{
	if( !P ) return 0;
	if( K < P->Key )
		P->Left = AVL_TREE_Remove(P->Left, K);
	else if( K > P->Key )
		P->Right = AVL_TREE_Remove(P->Right, K);
    else
	{
		struct AVL_TREE_Node* Q = P->Left;
		struct AVL_TREE_Node* R = P->Right;
		free(P);
		if( !R ) return Q;
		struct AVL_TREE_Node* Min = AVL_TREE_FindMin(R);
		Min->Right = AVL_TREE_RemoveMin(R);
		Min->Left = Q;
		return AVL_TREE_Balance(Min);
	}
	return AVL_TREE_Balance(P);
}
void AVL_TREE_Print(struct AVL_TREE_Node* P, int Tab)
{
    int i;
    if(P != NULL)
    {
        for(i = 0; i < Tab; i++) printf("|   ");
        AVL_TREE_Print(P->Left, Tab + 1);
        printf("%d\n", P->Key);
        AVL_TREE_Print(P->Right, Tab + 1);
    }
}
struct AVL_TREE_Node* AVL_TREE_Find(struct AVL_TREE_Node* P, int K)
{
    if(P == NULL)
        return NULL;
    if(P->Key == K)
        return P;
    if(P->Key < K)
        AVL_TREE_Find(P->Left, K);
    if(P->Key > K)
        AVL_TREE_Find(P->Right, K);
    return NULL;
};
void AVL_TREE_Destroy(struct AVL_TREE_Node* P)
{
    if(P)
    {
        AVL_TREE_Destroy(P->Left);
        AVL_TREE_Destroy(P->Right);
        free(P);
    }
}
/////////////
int main(void)
{
    freopen("AVL_TREE.out", "w", stdout);
    srand(time(0));
    struct AVL_TREE_Node* p = NULL;
    int i;
    for(i = 0; i < 100; i++)
        p = AVL_TREE_Insert(p, rand());
    AVL_TREE_Print(p, 0);
    return 0;
}
