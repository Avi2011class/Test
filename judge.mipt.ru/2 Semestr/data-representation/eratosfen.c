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

    int x, i, j;
    scanf("%d", &x);
    void* bitset = init_bitset(x + 1);

    for(i = 2; i * i <= x; i++)
        if(!get_bitset(bitset, i))
            for(j = i * i; j <= x; j += i)
                set_bitset(bitset, j, 1);

    int count = 0;
    for(i = 2; i <= x; i++)
        if(!get_bitset(bitset, i))
            count++;
    printf("%d", count);
    destroy_bitset(bitset);
    return 0;
}
