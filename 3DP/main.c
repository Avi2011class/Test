#include <stdio.h>
#include <stdlib.h>
#include "libvector.h"
int main(void)
{
    struct vector V1 = {3, 0, 4};
    struct vector V2 = {1, 1, 1};
    VectorPrintf(ProjectionVectorToLine(V1, V2));
    return 0;
}
