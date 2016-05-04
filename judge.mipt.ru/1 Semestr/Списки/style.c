#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    int n, m;
    scanf("%d %d", &n, &m);
    int* q = malloc(sizeof(int) * n);
    int i;
    for(i = 0; i < n; i++)
        q[i] = 1;

    int count = n;
    int iter = -1;
    while(count > 0)
    {
        int curl = 0;
        while(curl < m)
        {
            iter = (iter + 1) % n;
            if(q[iter])
                curl++;
        }
        q[iter] = 0;
        count -= 1;
        if(count < 3)
            printf("%d ", iter + 1);
    }
    free(q);
    return 0;
}
