#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

union Address
{
    char parts[4];
    uint32_t binary;
} __attribute__((packed));

union Address read (FILE* file)
{
    union Address a;
    fscanf (file, "%hhu.%hhu.%hhu.%hhu", &a.parts[3], &a.parts[2], &a.parts[1], &a.parts[0]);
    return a;
}

void write (FILE* file, union Address a)
{
    fprintf (file, "%hhu.%hhu.%hhu.%hhu", a.parts[3], a.parts[2], a.parts[1], a.parts[0]);
}

int main()
{
    union Address address = read (stdin), mask = read_address (stdin), broadcast;

    broadcast.binary = address.binary | ~mask.binary;

    write (stdout, broadcast);
    putchar ('\n');
}
