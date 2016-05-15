#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int* q1 = malloc(sizeof(int) * 100010);
    int* q2 = malloc(sizeof(int) * 100010);
    int i;
    for(i = 0; i < 5; i++)
        scanf("%d", &q1[i]);
    for(i = 0; i < 5; i++)
        scanf("%d", &q2[i]);

    int start1 = 0;
    int stop1 = 5;
    int start2 = 0;
    int stop2 = 5;
    int k, t;
    int step = 0;
    while((start1 - stop1) * (start2 -  stop2) != 0 && step < 1000000)
    {
        k = q1[start1];
        start1++;
        t = q2[start2];
        start2++;
        if(k == 0 && t == 9)
        {
            q1[stop1] = k;
            stop1++;
            q1[stop1] = t;
            stop1++;
        }
        else if(k == 9 && t == 0)
        {
            q2[stop2] = k;
            stop2++;
            q2[stop2] = t;
            stop2++;
        }
        else if(k > t)
        {
            q1[stop1] = k;
            stop1++;
            q1[stop1] = t;
            stop1++;
        }
        else if(k < t)
        {
            q2[stop2] = k;
            stop2++;
            q2[stop2] = t;
            stop2++;
        }
        step++;
    }

    if(step == 1000000)
        printf("botva\n");
    else
    {
        if(stop1 == start1)
            printf("second %d\n", step);
        if(stop2 == start2)
            printf("first %d\n", step);
    }
    free(q1);
    free(q2);
    return 0;
}
