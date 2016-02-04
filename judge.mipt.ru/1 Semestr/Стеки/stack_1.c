void stack_create(struct Stack * s)
{
    s->n = 0;
}

void stack_push(struct Stack * s, Data x)
{
    (s->a)[s->n] = x;
    s->n++;
}

Data stack_pop(struct Stack * s)
{
    Data mem = (s->a)[s->n - 1];
    s->n--;
    return mem;
}
Data stack_get(struct Stack * s)
{
    return (s->a)[s->n - 1];
}
void stack_print(struct Stack * s)
{
    if(s->n == 0)
    {
        printf("Empty stack\n");
        return;
    }
    int i = 0;
    for(i = 0; i < s->n; i++)
        printf("%d ", (s->a)[i]);
    printf("\n");
}
int  stack_size(struct Stack * s)
{
    return s->n;
}
void stack_clear(struct Stack * s)
{
    s->n = 0;
}