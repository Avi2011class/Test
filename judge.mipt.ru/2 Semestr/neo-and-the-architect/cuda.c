#include <stdio.h>
#include <math.h>

unsigned round_up(unsigned v, unsigned gr)
{
    unsigned tmp = v + gr - 1;
    return tmp - (tmp % gr);
}
int main()
{
    freopen("cuda.in", "r", stdin);
    freopen("cuda.out", "w", stdout);
    unsigned bt, tr, bm;
    scanf("%u %u %u", &bt, &tr, &bm);
    unsigned apb = round_up(bt, 32), arpb = round_up(tr, 2) * apb, amb = round_up(bm, 128);
    unsigned abt = apb ? (1536 / apb) : 8, abr = arpb ? (32768 / arpb) : 8, abm = amb ? (49152 / amb) : 8;
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN4(a, b, c, d) MIN(MIN(MIN(a, b), c), d)
    unsigned ab = MIN4(abt, abr, abm, 8);
    unsigned ut = ab * bt;
    long useful_load = lroundl(ut * 100 / (long double)1536);
    printf("%ld\n", useful_load);
    return 0;
}
