#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, i;
    scanf("%d %d", &n, &m);
    int* q = malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
        q[i] = 1;
    int c = n;
    int iter = -1;
    while (c > 0)
    {
        int curl = 0;
        while (curl < m)
        {
            iter = (iter + 1) % n;
            if(q[iter] != 0)
                curl += 1;
        }
        q[iter] = 0;
        c -= 1;
        if(c < 3)
            printf("%d ", iter + 1);
    }
    free(q);
    return 0;
}
