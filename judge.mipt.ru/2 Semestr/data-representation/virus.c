#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
void* init_bitset(size_t N)
{
    return calloc(1, (N + 7) / 8);
}
void destroy_bitset(void* bitset)
{
    free(bitset);
}
void set_bitset(void* bitset, size_t N, unsigned bit)
{
    size_t byte_id = N / 8;
    size_t bit_id = N % 8;
    uint8_t* byte = (uint8_t*)bitset + byte_id;
    if(bit)
        *byte |= (1 << bit_id);
    else
        *byte &= ~(1 << bit_id);
}
int get_bitset(void* bitset, size_t N)
{
    size_t byte_id = N / 8;
    size_t bit_id = N % 8;
    uint8_t* byte = (uint8_t*)bitset + byte_id;
    return (*byte >> bit_id) & 1;
}

int main(void)
{
    size_t infected, count, i, j;
    scanf ("%zu %zu", &infected, &count);
    void* bitset = init_bitset (count);
    for (i = 0; i < infected; ++i)
    {
        size_t nr;
        scanf ("%zu", &nr);
        size_t delta = nr;
        for (j = nr; j < count; j += delta++)
            set_bitset (bitset, j, 1);
    }

    size_t infected_count = 0;
    for (i = 0; i < count; ++i)
        if (get_bitset (bitset, i))
            ++infected_count;

    destroy_bitset (bitset);
    printf ("%zu\n", infected_count);
    return 0;
}
