struct List * list_create ()
{
    struct List* cur = (struct List*)malloc(sizeof(struct List));
    cur->head = NULL;
    return cur;
};

void list_add_first (struct List * list, Data x)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->next = list->head;
    list->head = new_node;
    new_node->val = x;
}
void list_add_last (struct List * list, Data x)
{
    struct Node* cur = list->head;
    while(cur->next != NULL)
        cur = cur->next;
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->next = NULL;
    new_node->val = x;
    cur->next = new_node;
}
Data list_remove_first (struct List * list)
{
    Data res = list->head->val;
    struct Node* new_node = (list->head)->next;
    free(list->head);
    list->head = new_node;
    return res;
}

Data list_remove_last (struct List * list)
{
    struct Node* cur = list->head;
    if(cur->next == NULL)
    {
        Data res = cur->val;
        free(list->head);
        list->head = NULL;
        return res;
    }
    else
    {
        struct Node* cur = list->head;
        while(cur->next->next != NULL)
            cur = cur->next;
        Data res = cur->next->val;
        free(cur->next);
        cur->next = NULL;
        return res;

    }
    return 0;
}
Data list_get_first (struct List * list)
{
    return list->head->val;
}
Data list_get_last (struct List * list)
{
    struct Node* cur = list->head;
    while(cur->next != NULL)
        cur = cur->next;
    return cur->val;
}
void list_print (struct List * list)
{
    if(list->head == NULL)
        printf("Empty list\n");
    else
    {
        struct Node* cur = list->head;
        while(cur != NULL)
        {
            printf("%d ", cur->val);
            cur = cur->next;
        }
        printf("\n");
    }
}
int list_size(struct List * list)
{
    int res = 0;
    struct Node* cur = list->head;
    while(cur != NULL)
    {
        res++;
        cur = cur->next;
    }
    return res;
}
void list_clear(struct List * list)
{
    struct Node* cur = list->head;
    while(cur != NULL)
    {
        struct Node* mem = cur;
        free(cur);
        cur = mem->next;
    }
    list->head = NULL;
}
void list_destroy (struct List * list)
{
    struct Node* cur = list->head;
    while(cur != NULL)
    {
        struct Node* mem = cur;
        free(cur);
        cur = mem->next;
    }
    free(list);
}
