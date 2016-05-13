#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint16_t adr;

byte mem[UINT16_MAX];

byte b_read(adr a)
{
    return mem[a];
}
void b_write(adr a, byte val)
{
    mem[a] = val;
}
word w_read(adr a)
{
    return le16toh(*(word *) (mem + a));
}
void w_write(adr a, word val)
{
    *(word *) (mem + a) = htole16(val);
}

void load_file(void)
{
    scanf(" ");
    while (!feof(stdin))
    {
        adr off;
        word size;
        scanf("%hx %hx", &off, &size);
        word i;
        for (i = 0; i < size; i++)
        {
            byte b;
            scanf("%hhx", &b);
            b_write(off + i, b);
        }
        scanf(" ");
    }
}
void mem_dump(adr start, word n)
{
    word i;
    for (i = 0; i < n; i += 2)
    {
        word w = w_read(start + i);
        printf("%06o : %06o\n", start + i, w);
    }
}
