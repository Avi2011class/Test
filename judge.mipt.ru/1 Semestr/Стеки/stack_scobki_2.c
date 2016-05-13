#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define N 10000

struct Stack
{
    int n;
    int a[N];
};
void stack_create(struct Stack * s)
{
    s->n=0;
};
void stack_push(struct Stack * s, int x)
{
    s->a[s->n]=x;
    (s->n)++;
};
int stack_pop(struct Stack * s)
{
    int m;
    m=s->a[(s->n)-1];
    (s->n)--;
    return m;
};
int stack_get(struct Stack * s)
{
    int m=s->a[(s->n)-1];
    return m;
};
void stack_print(struct Stack * s)
{
    int i;
    for (i=0; i<(s->n); i++)
        printf ( "%d ", s->a[i]);
    printf ( "\n" );
};
int stack_size(struct Stack * s)
{
    return s->n;
};
void stack_clear(struct Stack * s)
{
    s->n=0;
}

int main()
{
    struct Stack* a=malloc(sizeof(struct Stack));
    stack_create(a);
    char s[10000];
    int b[10000],i;
    int l,x,c;
    scanf( "%s" , s );
    int m = strlen(s);
    for ( i = 0 ; i < m ; i++ )
    {
        if ( s[i] == '(' ) b[i] = -1;
        if ( s[i] == '[' ) b[i] = -2;
        if ( s[i] == '{' ) b[i] = -3;
        if ( s[i] == '<' ) b[i] = -4;
        if ( s[i] == ')' ) b[i] = 1;
        if ( s[i] == ']' ) b[i] = 2;
        if ( s[i] == '}' ) b[i] = 3;
        if ( s[i] == '>' ) b[i] = 4;
    }
    for ( i = 0; i < m ; i++ )
    {
        if ( b[i] < 0 )
        {
            stack_push(a, b[i]);
        }
        if ( b[i] > 0 )
        {
            l = stack_get(a);
            if ( ( l + b[i] ) != 0 )
            {
                stack_push(a, b[i]);
            }
            if (( l + b[i] ) == 0 )
                x = stack_pop(a);
        };
    }
    c = stack_size(a);
    if (c==0)
    {
        printf( "YES" );
    }
    else printf( "NO" );
    free(a);
    return 0;
}