#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int x;
    sscanf(argv[1], "%x", &x);
    printf((x & 1) ? "ma" : "fe");
    return 0;
}
