#ifndef MEMORYCONTROLLER_H_INCLUDED
#define MEMORYCONTROLLER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_TYPE char
#define BLOCK_HEIGHT 5
#define BLOCK_WIDTH 5
#define BLOCK_SIZE ( BLOCK_HEIGHT * BLOCK_WIDTH * sizeof (BLOCK_TYPE) )

struct MemoryAllocator
{
	BLOCK_TYPE* freeMemory;
	uint8_t* isFree;
	int allocationStep;
	int size;
	int freeSize;
};
struct MemoryAllocator* initMemoryAllocator (int allocationStep);
void destroyMemoryAllocator (struct MemoryAllocator* this);
void dumpMemoryAllocator (struct MemoryAllocator* this, FILE* outputStream);
BLOCK_TYPE* getMemoryFromAllocator (struct MemoryAllocator* this);
void freeMemoryFromAllocator (struct MemoryAllocator* this, BLOCK_TYPE* memory);
#endif // MEMORYCONTROLLER_H_INCLUDED
