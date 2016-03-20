#include <stdio.h>
#include <stdlib.h>

struct _Data16Bit
{
    char Memory[16];
};
typedef struct _Data16Bit Data;
void FreeData16Bit(Data* Memory)
{
    size_t i;
    char* Iterator = (char*)Memory;
    for(i = 0; i < 16; i++, Iterator++)
        *Iterator = 0;
}
struct MemoryAllocator
{
    int FullSize;
    int AllocatorStep;
    int FreeCount;
    void (*FreeFunction)(Data*);
    int* CanBeUsed;
    Data* FreeMemory;
};
inline struct MemoryAllocator* CreateMemoryAllocator(int AllocatorStep, void (*FreeFunction)(Data*))
{
    size_t i, j;
    struct MemoryAllocator* NewAllocator = (struct MemoryAllocator*)malloc(sizeof(struct MemoryAllocator));
    NewAllocator->FullSize = AllocatorStep;
    NewAllocator->AllocatorStep = AllocatorStep;
    NewAllocator->FreeCount = AllocatorStep;
    NewAllocator->FreeFunction = FreeFunction;
    NewAllocator->CanBeUsed = (int*)malloc(sizeof(int) * AllocatorStep);
    for(i = 0; i < AllocatorStep; i++)
        NewAllocator->CanBeUsed[i] = 1;

    NewAllocator->FreeMemory = (Data*)malloc(sizeof(Data) * AllocatorStep);
    for(i = 0; i < AllocatorStep; i++)
        FreeFunction(&(NewAllocator->FreeMemory[i]));
    return NewAllocator;
};


int main(void)
{
    struct MemoryAllocator* Allocator = CreateMemoryAllocator(10, FreeData16Bit);
    return 0;
}
