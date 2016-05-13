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