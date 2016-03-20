#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    char a, b;
    uint8_t mask = 0;
    while(scanf("%c%c ", &a, &b) == 2)
    {
        if(a == 'm' && b == 'a')
            mask |= 1;
        if(a == 'c' && b == 'l')
            mask |= 2;
        if(a == 'h' && b == 'a')
            mask |= 4;
        if(a == 't' && b == 'r')
            mask |= 8;

        if(a == 'r' && b == 'd')
            mask |= 16;
        if(a == 'b' && b == 'w')
            mask |= 32;
        if(a == 'b' && b == 'k')
            mask |= 16 + 32;

        if(a == 'g' && b == 'e')
            mask |= 64;
        if(a == 'g' && b == 'y')
            mask |= 128;
        if(a == 'd' && b == 'a')
            mask |= 64 + 128;
    }
    printf("%hhx", mask);
    return 0;
}
