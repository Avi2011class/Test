#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct vector
{
    double x;
    double y;
    double z;
};
inline struct vector VectorCreate(double x, double y, double z)
{
    struct vector Res;
    Res.x = x;
    Res.y = y;
    Res.z = z;
    return Res;
}
inline struct vector VectorAdd(struct vector V1, struct vector V2)
{
    struct vector Result = {V1.x + V2.x, V1.y + V2.y, V1.z + V2.z};
    return Result;
};
inline struct vector VectorSub(struct vector V1, struct vector V2)
{
    struct vector Result = {V1.x - V2.x, V1.y - V2.y, V1.z - V2.z};
    return Result;
};
inline struct vector VectorMul(struct vector V, double k)
{
    struct vector Result = {V.x * k, V.y * k, V.z * k};
    return Result;
};
inline double ScalarProduct(struct vector V1, struct vector V2)
{
    return V1.x * V2.x + V1.y * V2.y + V1.z * V2.z;
}
inline struct vector VectorProduct(struct vector V1, struct vector V2)
{
    struct vector Result = {V1.y * V2.z - V1.z * V2.y, V1.z * V2.x - V1.x * V2.z, V1.x * V2.y - V2.x * V1.y };
    return Result;
};
inline double MixedProduct(struct vector V1, struct vector V2, struct vector V3)
{
    return ScalarProduct(V1, VectorProduct(V2, V3));
};
inline double VectorLength(struct vector V)
{
    return sqrt(V.x * V.x + V.y * V.y + V.z * V.z);
}
inline double VectorCos(struct vector V1, struct vector V2)
{
    double Len1 = VectorLength(V1);
    double Len2 = VectorLength(V2);
    if(Len1 * Len2 == 0)
        return 0;
    return ScalarProduct(V1, V2) / Len1 / Len2;
}
inline struct vector ProjectionVectorToLine(struct vector V, struct vector Line)
{
    double Len = VectorLength(Line);
    return VectorMul(Line, ScalarProduct(V, Line) / Len / Len);
}
inline struct vector ProjectionVectorToPlane(struct vector V, struct vector N)
{
    return VectorSub(V, ProjectionVectorToLine(V, N));
}
inline void VectorPrintf(struct vector V)
{
    printf("(%lg, %lg, %lg)\n", V.x, V.y, V.z);
}
