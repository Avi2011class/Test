#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int x, a;
    scanf("%x", &x);

    if(x & 1)
        printf("ma ");
    else
        printf("fe ");

    if(x & 2)
        printf("cl ");
    else
        printf("du ");

    if(x & 4)
        printf("ha ");
    else
        printf("nh ");

    if(x & 8)
        printf("tr ");
    else
        printf("sk ");

    a = x & (16 + 32);
    if(a == 0)
        printf("bn ");
    if(a == 16)
        printf("rd ");
    if(a == 32)
        printf("bw ");
    if(a == 48)
        printf("bk ");

    a = x & (64 + 128);
    if(a == 0)
        printf("bu");
    if(a == 64)
        printf("ge");
    if(a == 128)
        printf("gy");
    if(a == 128 + 64)
        printf("da");
    return 0;
}
