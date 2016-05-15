#include <stdio.h>
#include <stdlib.h>
typedef int Data;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

struct Node
{
    Data val;            // данные в узле
    struct Node * left;  // левый ребенок
    struct Node * right; // правый ребенок
    int h;
};
int res = 0;

struct Node * tree_add (struct Node * tree, Data x, int len)
{
    if(tree == NULL)
    {
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->left = NULL;
        node->right = NULL;
        node->val = x;
        node->h = len;
        res = max(res, len);
        return node;
    }
    else
    {
        if(x < tree->val)
        {
            tree->left = tree_add(tree->left, x, len + 1);

            return tree;
        }
        if(x > tree->val)
        {
            tree->right = tree_add(tree->right, x, len + 1);
            return tree;
        }
    }
    return tree;
};


void tree_print (struct Node * tree)
{
    if(tree != NULL)
    {
        tree_print(tree->left);
        printf("%d ", (int)(tree->val));
        tree_print(tree->right);
    }
}

void tree_destroy (struct Node * tree)
{
    if(tree != NULL)
    {
        if(tree->left)tree_destroy(tree->left);
        if(tree->right)tree_destroy(tree->right);
        free(tree);
    }

}
int main(void)
{
    struct Node * tree=NULL;
    int i;
    while(1)
    {
        scanf("%d", &i);
        if(i == 0) break;
        else tree = tree_add(tree, i, 1);
    }
    printf("%d\n", res);
    tree_destroy(tree);
    return 0;
}