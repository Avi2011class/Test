#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char ch;
    scanf("%c", &ch);
    if(ch == '0')
        printf("0");
    if(ch == '1')
        printf("1");
    if(ch == '2')
        printf("10");
    if(ch == '3')
        printf("11");
    if(ch == '4')
        printf("100");
    if(ch == '5')
        printf("101");
    if(ch == '6')
        printf("110");
    if(ch == '7')
        printf("111");
    if(ch == '8')
        printf("1000");
    if(ch == '9')
        printf("1001");
    if(ch == 'A')
        printf("1010");
    if(ch == 'B')
        printf("1011");
    if(ch == 'C')
        printf("1100");
    if(ch == 'D')
        printf("1101");
    if(ch == 'E')
        printf("1110");
    if(ch == 'F')
        printf("1111");

    if(scanf("%c", &ch) <= 0)
        return 0;

    while(ch != "\n")
    {
        if(ch == '0')
            printf("0000");
        if(ch == '1')
            printf("0001");
        if(ch == '2')
            printf("0010");
        if(ch == '3')
            printf("0011");
        if(ch == '4')
            printf("0100");
        if(ch == '5')
            printf("0101");
        if(ch == '6')
            printf("0110");
        if(ch == '7')
            printf("0111");
        if(ch == '8')
            printf("1000");
        if(ch == '9')
            printf("1001");
        if(ch == 'A')
            printf("1010");
        if(ch == 'B')
            printf("1011");
        if(ch == 'C')
            printf("1100");
        if(ch == 'D')
            printf("1101");
        if(ch == 'E')
            printf("1110");
        if(ch == 'F')
            printf("1111");
        if(scanf("%c", &ch) <= 0)
            break;
    }
    return 0;
}