#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    size_t count;
    uint32_t *table, address;

	unsigned int mask = ((1 << 26) - 1);

    scanf("%zu", &count);
    table = malloc(sizeof(*table) * count);
    size_t i;
    for (i = 0; i < count; i++)
		scanf("%x", &table[i]);

    scanf("%x", &address);

    size_t id = address >> 26;
    if (id < count)
    {
        uint32_t offset = address & mask;
        printf("%x\n", table[id] + offset);
    }
    else
		printf("error\n");
}
