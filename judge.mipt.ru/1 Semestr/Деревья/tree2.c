#include <stdio.h>
#include <stdlib.h>
typedef int Data;

struct Node
{
    Data val;            // ������ � ����
    struct Node * left;  // ����� �������
    struct Node * right; // ������ �������
};

struct Node * tree_add (struct Node * tree, Data x)
{
    if(tree == NULL)
    {
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->left = NULL;
        node->right = NULL;
        node->val = x;
        return node;
    }
    else
    {
        if(x < tree->val)
        {
            tree->left = tree_add(tree->left, x);
            return tree;
        }
        if(x > tree->val)
        {
            tree->right = tree_add(tree->right, x);
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
        else tree = tree_add(tree, i);
    }
    tree_print(tree);   // ���������� 1 2 3 4 5 6 7 8 9
    tree_destroy(tree);
    return 0;
}