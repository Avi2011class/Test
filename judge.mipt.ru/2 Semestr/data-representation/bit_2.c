#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int x;
    scanf("%x", &x);
    printf((x & 4) ? "ha" : "nh");
    return 0;
}
