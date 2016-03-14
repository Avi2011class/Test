#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct BitSet
{
    size_t length;
    void* data;
};
int bitset_OK(struct BitSet* This)
{
    return This && This->length && This->data;
}
struct BitSet* create_bitset(size_t length)
{
    struct BitSet* new_bitset = (struct BitSet*)calloc(1, sizeof(struct BitSet));
    if(new_bitset == NULL)
        return NULL;
    new_bitset->data = (void*) calloc(1, (length + 7) / 8 + 1);
    if(new_bitset->data == NULL)
        return NULL;
    new_bitset->length = length;
    return new_bitset;
};
void destroy_bitset(struct BitSet* This)
{
    if(!bitset_OK(This))
        return;
    if(This->length > 0)
        free(This->data);
    free(This);
}
int bitset_get_bit(struct BitSet* This, size_t number_of_bit)
{
    if(!bitset_OK(This))
        return -1;
    if(number_of_bit >= This->length)
        return -1;
    size_t byte_id = number_of_bit / 8;
	size_t bit_id = number_of_bit % 8;
	uint8_t* byte = (uint8_t*)(This->data) + byte_id;
	return (*byte >> bit_id) & 1;
}
void bitset_set_bit(struct BitSet* This, size_t number_of_bit, uint8_t value)
{
    if(!bitset_OK(This))
        return;
    if(number_of_bit >= This->length)
        return;
    size_t byte_id = number_of_bit / 8;
	size_t bit_id = number_of_bit % 8;
	uint8_t* byte = (uint8_t*)(This->data) + byte_id;
    if (value)
        *byte |= 1 << bit_id;
    else
        *byte &= ~(1 << bit_id);
}
void bitset_print(struct BitSet* This)
{
    if(!bitset_OK(This))
        printf("Incorrect bitset!\n");
    printf("Bitset:\n size: %u\n data: ", This->length);
    size_t i;
    for(i = 0; i < This->length; i++)
    {
        printf("%d", bitset_get_bit(This, i));
        if(i % 8 == 7)
            printf(" : ");
    }
    printf("\n");
}

int main(void)
{
    struct BitSet* B = create_bitset(30);
    bitset_set_bit(B, 29, 1);
    bitset_set_bit(B, 8, 1);
    bitset_set_bit(B, 0, 1);
    bitset_print(B);
    bitset_set_bit(B, 8, 0);
    bitset_print(B);
    return 0;
}
