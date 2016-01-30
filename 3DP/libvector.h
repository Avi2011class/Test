struct vector
{
    double x;
    double y;
    double z;
};
struct vector VectorCreate(long double x, long double y, long double z);
struct vector VectorAdd(struct vector V1, struct vector V2);
struct vector VectorSub(struct vector V1, struct vector V2);
struct vector VectorMul(struct vector V, long double k);
long double ScalarProduct(struct vector V1, struct vector V2);
struct vector VectorProduct(struct vector V1, struct vector V2);
long double MixedProduct(struct vector V1, struct vector V2, struct vector V3);
long double VectorLength(struct vector V);
long double VectorCos(struct vector V1, struct vector V2);
inline struct vector ProjectionVectorToLine(struct vector V, struct vector Line);
void VectorPrintf(struct vector V);
inline struct vector ProjectionVectorToPlane(struct vector V, struct vector N);