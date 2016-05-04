#include <stdio.h>
#include <stdlib.h>
int min(int a, int b)
{
    return (a < b) ? a : b;
}

int main()
{
    int N, M,k,i,t,x;
    struct ver
    {
        int put;
        int bili;
    };
    struct ver a[100];
    scanf( "%d%d" , &N, &M );
    int b[5000][3];
    for ( i = 0 ; i < M ; i++ )
    {
        for ( k = 0 ; k < 3 ; k++ )
        {
            scanf("%d", &b[i][k]);
        };
    }
    scanf("%d", &t);
    a[t].put=0;
    a[t].bili=0;
    for (i = 0; i < N; i++)
        if (i != t)
        {
            a[i].bili = 0;
            a[i].put = 1000000;
        }
    for (i = t; i < N; i++)
        for (k = 0; k < M; k++)
        {
                a[b[k][1]].put = min(a[b[k][1]].put, a[b[k][0]].put + b[k][2]);
                a[b[k][0]].put = min(a[b[k][0]].put, a[b[k][1]].put + b[k][2]);
        }
        /*
    for ( i = 0 ; i < t ; i++ )
    {
        for ( k = 0 ; k < M ; k++ )
        {
            if (( b[k][0] == i )||( b[k][1] == i ))
            {
                if ((a[b[k][1]].bili == 0)&&((a[i].put+b[k][2])<a[b[k][1]].put))
                    a[b[k][1]].put=a[i].put+b[k][2];
            };

        };
    }
    */
    for (i=0; i<N; i++)
    {
        printf("%d ", a[i].put);

    }
    return 0;
}