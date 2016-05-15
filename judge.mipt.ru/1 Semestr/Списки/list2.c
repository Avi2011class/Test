void list_init(struct Node * list)
{
    list->next = list;
    list->prev = list;
    list->data = 0;
}
void list_insert(struct Node * list, struct Node * t)
{
    struct Node* n = list->next;
    list->next = t;
    t->next = n;
    n->prev = t;
    t->prev = list;
}
void list_insert_before(struct Node * list, struct Node * t)
{
    struct Node* prev = list->prev;
    list->prev = t;
    t->prev = prev;
    prev->next = t;
    t->next = list;
}
void list_remove(struct Node * t)
{
    t->next->prev = t->prev;
    t->prev->next = t->next;
}
struct Node * list_push_front(struct Node * list, Data d)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    list_insert(list, new_node);
    return list;
}
struct Node * list_push_back(struct Node * list, Data d)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    list_insert(list->prev->prev, new_node);
    return list;
};
Data list_pop_front(struct Node * list)
{
    Data res = list->next->data;
    list_remove(list->next);
    return res;
}
Data list_pop_back(struct Node * list)
{
    Data res = list->prev->data;
    list_remove(list->prev);
    return res;
}
Data list_delete(struct Node * t)
{
    Data res = t->data;
    t->next->prev = t->prev;
    t->prev->next = t->next;
    return res;
}
void list_print (struct Node * list)
{
    if(list->next == list)
        printf("Empty list\n");
    else
    {
        struct Node* cur = list->next;
        while(cur != list)
        {
            printf("%d ", cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
}
Data list_sum (struct Node * list)
{
    Data res = 0;
    if(list->next != list)
    {
        struct Node* cur = list->next;
        while(cur != list)
        {
            res += cur->data;
            cur = cur->next;
        }
    }
    return res;
}
int list_is_empty(struct Node * list)
{
    return (list == list->next);
}
int list_clear(struct Node * list)
{
    if(list->next != list)
    {
        struct Node* cur = list->next;
        while(cur != list)
        {
            struct Node* mem = cur;
            cur = cur->next;
            free(mem);
        }
    }
    list->next = list;
    list->prev = list;
    return 0;
}
void list_foreach(struct Node * list, void (*func)(Data d, void * param), void * param)
{
    if(list->next != list)
    {
        struct Node* cur = list->next;
        while(cur != list)
        {
            func(cur->data, param);
            cur = cur->next;
        }
    }
}
