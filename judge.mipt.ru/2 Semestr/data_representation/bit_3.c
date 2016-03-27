#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int x;
    scanf("%x", &x);
    x = x & (16 + 32);
    if(x == 0)
        printf("bn");
    if(x == 16)
        printf("rd");
    if(x == 32)
        printf("bw");
    if(x == 48)
        printf("bk");
    return 0;
}
