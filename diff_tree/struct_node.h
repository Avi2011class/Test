#ifndef STRUCT_NODE_H_INCLUDED
#define STRUCT_NODE_H_INCLUDED

struct __tree_node
{
    uint8_t type;
    struct __tree_node* pointer_left;
    struct __tree_node* pointer_right;
    struct __tree_node* pointer_down;
    long double constant_value;
};

struct __tree_node* create_tree_node(uint8_t type)
{
    struct __tree_node* new_node = (struct __tree_node*)calloc(1, sizeof(struct __tree_node));
    new_node->type = type;
    new_node->pointer_left = NULL;
    new_node->pointer_right = NULL;
    new_node->pointer_down = NULL;
    new_node->constant_value = 0;
    return new_node;
};



#endif // STRUCT_NODE_H_INCLUDED
