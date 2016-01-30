#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Data;

int CompareData(Data First, Data Second)
{
    return First - Second;
}
/*------------------------TREE--------------------*/
struct TreeNode
{
    Data Value;
    struct TreeNode* Left;
    struct TreeNode* Right;
};
struct TreeNode* TreeAdd(struct TreeNode* Tree, Data Value)
{
    if(Tree == NULL)
    {
        struct TreeNode* NewNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        NewNode->Value = Value;
        NewNode->Left = NULL;
        NewNode->Right = NULL;
        return NewNode;
    }
    if(CompareData(Tree->Value, Value) > 0)
    {
        Tree->Left = TreeAdd(Tree->Left, Value);
        return Tree;
    }
    if(CompareData(Tree->Value, Value) < 0)
    {
        Tree->Right = TreeAdd(Tree->Right, Value);
        return Tree;
    }
    return Tree;
}
struct TreeNode* TreeAddNode(struct TreeNode* Tree, struct TreeNode* Add)
{
    if(Add == NULL && Tree == NULL)
        return NULL;
    if(Add == NULL)
        return Tree;
    if(Tree == NULL)
        return Add;

    struct TreeNode* Buf = Add;
    Add = Tree;
    Tree = Buf;

    if(CompareData(Tree->Value, Add->Value) > 0)
    {
        Tree->Left = TreeAddNode(Tree->Left, Add);
        return Tree;
    }
    if(CompareData(Tree->Value, Add->Value) < 0)
    {
        Tree->Right = TreeAddNode(Tree->Right, Add);
        return Tree;
    }
    return Tree;
}
struct TreeNode* TreeFind(struct TreeNode* Tree, Data Value)
{
    if(Tree == NULL)
        return NULL;
    if(CompareData(Tree->Value, Value) == 0)
        return Tree;
    if(CompareData(Tree->Value, Value) > 0)
        return TreeFind(Tree->Left, Value);
    if(CompareData(Tree->Value, Value) < 0)
        return TreeFind(Tree->Right, Value);
    return NULL;
}
struct TreeNode* TreeErase(struct TreeNode* Tree, Data Value)
{
    if(Tree == NULL)
        return NULL;
    if(CompareData(Tree->Value, Value) == 0)
    {
        struct TreeNode* Temp = TreeAddNode(Tree->Left, Tree->Right);
        free(Tree);
        return Temp;
    }
    if(CompareData(Tree->Value, Value) > 0)
        if(Tree->Left != NULL)
            Tree->Left = TreeErase(Tree->Left, Value);
    if(CompareData(Tree->Value, Value) < 0)
        if(Tree->Right != NULL)
            Tree->Right = TreeErase(Tree->Right, Value);
    return Tree;
}
void TreeDestroy(struct TreeNode* Tree)
{
    if(Tree == NULL)
        return;
    TreeDestroy(Tree->Left);
    TreeDestroy(Tree->Right);
    free(Tree);
}
void TreePrint(struct TreeNode* Tree, int Tab)
{
    if(Tree != NULL)
    {
        if(Tree->Left != NULL)
            TreePrint(Tree->Left, Tab + 1);
        int i;
        printf("%d ", Tree->Value);
        if(Tree->Right != NULL)
            TreePrint(Tree->Right, Tab + 1);
    }
    if(Tab == 0)
        printf("\n");
}
/*------------------------------SET--------------------------------*/
struct Set
{
    int Size;
    struct TreeNode* Head;
};
struct Set* SetCreate()
{
    struct Set* NewSet = (struct Set*)malloc(sizeof(struct Set));
    NewSet->Size = 0;
    NewSet->Head = NULL;
    return NewSet;
}
int SetSize(struct Set* Set)
{
    return Set->Size;
}
int SetFind(struct Set* Set, Data Value)
{
    struct TreeNode* Tmp = TreeFind(Set->Head, Value);
    return (Tmp != NULL) ? 1 : 0;
}
void SetInsert(struct Set* Se, Data Value)
{
    if(TreeFind(Se->Head, Value) == NULL)
    {
        (Se->Size)++;
        Se->Head = TreeAdd(Se->Head, Value);
    }
}
void SetErase(struct Set* Se, Data Value)
{
    struct TreeNode* Tmp = TreeFind(Se->Head, Value);
    if(Tmp != NULL)
    {
        Se->Size--;
        Se->Head = TreeErase(Se->Head, Value);
    }
}
void SetPrint(struct Set* Se)
{
    printf("Set, size = %d\n   ", Se->Size);
    TreePrint(Se->Head, 0);
}
void SetDestroy(struct Set* Se)
{
    TreeDestroy(Se->Head);
    free(Se);
}
/*-------------------------------------------------------------------------*/
int main(void)
{
    srand(time(0));
    struct TreeNode* S = SetCreate();
    int i;
    int n = 20;
    for(i = 0; i < n; i++)
    {
        int t = rand() % n;
        printf("Add %d\n", t);
        SetInsert(S, t);
        SetPrint(S);
    }
    printf("\n\n ERASE TEST\n");
    for(i = 0; i < n; i++)
    {
        int t = rand() % n;
        if(SetFind(S, t))
            printf("Tree Find %3d Yes\n");
        else
            printf("Tree Find %3d No\n");
        SetErase(S, t);
        SetPrint(S);
    }
    SetDestroy(S);
    return 0;
}
