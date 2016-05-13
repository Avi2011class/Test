#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000
typedef char Data;

struct Stack
{
    int n;
    Data a[N];
};


void stack_create(struct Stack * s);
void stack_push(struct Stack * s, Data x);
Data stack_pop(struct Stack * s);
Data stack_get(struct Stack * s);
void stack_print(struct Stack * s);
int  stack_size(struct Stack * s);
void stack_clear(struct Stack * s);


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

int main(void)
{
    int x;
    struct Stack s;
    stack_create(&s);
    char ss[10000];
    scanf("%s", ss);

    int l = strlen(ss);
    int i = 0;
    for(i = 0; i < l; i++)
    {
        if(stack_size(&s) == 0)
            stack_push(&s, ss[i]);
        else
        {
            char top = stack_get(&s);
            if((ss[i] == '>' && top == '<') || (ss[i] == ')' && top == '(') || (ss[i] == ']' && top == '[') || (ss[i] == '}' && top == '{'))
                stack_pop(&s);
            else
                stack_push(&s, ss[i]);
        }

    }
    (stack_size(&s) == 0) ? printf("YES\n") : printf("NO\n");
    return 0;
}