#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char* s = 0;
    scanf("%ms", &s);
    int nu = 0, le = strlen(s);
    while(nu < le)
    {
        if(s[nu] == '.')
            break;
        nu++;
    }
    double res = 0;
    int i;

    double mo = 1;
    i = nu - 1;
    while(i >= 0)
    {
        res += mo * (s[i] == '1');
        mo *= 2;
        i--;
    }
    if(nu != le)
    {
        mo = 0.5;
        i = nu + 1;
        while(i < le)
        {
            res += mo * (s[i] == '1');
            mo = mo / 2;
            i++;
        }
    }
    printf("%.12lf", res);
    free(s);
    return 0;
}