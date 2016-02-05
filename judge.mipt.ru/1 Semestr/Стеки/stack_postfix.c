#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 10000
typedef int Data;

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
    char ch;

    int i = 0;
    while(1)
    {
        scanf("%c", &ch);
        if(ch != ' ')
        {
            if(ch == '=')
            break;
        if(isdigit(ch))
            stack_push(&s, ch - 48);
        else
        {
            int b = stack_pop(&s);
            int a = stack_pop(&s);
            switch (ch)
            {
            case '+':
                a = a + b;
                break;
            case '-':
                a = a - b;
                break;
            case '*':
                a = a * b;
                break;
            }
            stack_push(&s, a);
        }
        }

    }

    printf("%d\n", stack_get(&s));

    return 0;
}