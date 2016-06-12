
#include "memoryController.h"

//#define DEBUG

struct MemoryAllocator* initMemoryAllocator (int allocationStep)
{
	struct MemoryAllocator* __new = (struct MemoryAllocator*) malloc (sizeof (struct MemoryAllocator));
	__new->size = allocationStep;
	__new->allocationStep = allocationStep;
	__new->freeSize = allocationStep;
	__new->isFree = (uint8_t*) calloc (allocationStep, sizeof (uint8_t));
	memset (__new->isFree, 1, allocationStep);
	__new->freeMemory = (BLOCK_TYPE*) calloc (allocationStep, BLOCK_SIZE);
#ifdef DEBUG
	printf("Memory allocator initialization completed\n");
#endif // DEBUG
	return __new;
};

void destroyMemoryAllocator (struct MemoryAllocator* this)
{
#ifdef DEBUG
	printf ("<==Destroy memory allocator\n");
	dumpMemoryAllocator (this, stdout);
#endif // DEBUG
	free (this->isFree);
	free (this->freeMemory);
	free (this);
}

void dumpMemoryAllocator (struct MemoryAllocator* this, FILE* outputStream)
{
	fprintf (outputStream, "Memory allocator dump:\n");
	fprintf (outputStream, "	this->size = %d\n", this->size);
	fprintf (outputStream, "	this->freeSize = %d\n", this->freeSize);
	fprintf (outputStream, "	this->allocationStep = %d\n", this->allocationStep);
	fprintf (outputStream, "	this->isFree:\n		");
	register unsigned int iterator = 0;
	for (iterator = 0; iterator < this->size; iterator++)
	{
		fprintf (outputStream, "%3x : %hhd	", iterator, this->isFree[iterator]);
		if (iterator % 8 == 7)
			fprintf (outputStream, "\n		");
	}
	fprintf (outputStream, "\n\n");
}

BLOCK_TYPE* getMemoryFromAllocator (struct MemoryAllocator* this)
{
#ifdef DEBUG
	printf ("<==getMemoryFromAllocator\n");
	dumpMemoryAllocator (this, stdout);
#endif // DEBUG
	if (this->freeSize > 0)
	{
		register int iterator;
		for (iterator = 0; iterator < this->size; iterator++)
			if (this->isFree[iterator])
			{
				this->isFree[iterator] = 0;
				this->freeSize--;
				memset (this->freeMemory + (BLOCK_SIZE * iterator), 0, BLOCK_SIZE);
				#ifdef DEBUG
					printf ("-->return memory from index = %d\n", iterator);
				#endif // DEBUG
				return this->freeMemory + (BLOCK_SIZE * iterator);
			}
	}
	else
	{
		this->freeSize += this->allocationStep - 1;
		this->isFree = (uint8_t*) realloc (this->isFree,
				sizeof (uint8_t) * (this->size + this->allocationStep));
		this->freeMemory = (BLOCK_TYPE*) realloc (this->freeMemory,
				BLOCK_SIZE * (this->size + this->allocationStep));
		register unsigned int iterator;
		for(iterator = this->size; iterator < this->size + this->allocationStep; iterator++)
			this->isFree[iterator] = 1;
		#ifdef DEBUG
			printf ("-->Resize memory allocator to size = %d\n", this->size + this->allocationStep);
		#endif // DEBUG
		this->isFree[this->size] = 0;
		this->size += this->allocationStep;
		memset (this->freeMemory + (BLOCK_SIZE * (this->size - this->allocationStep)), 0, BLOCK_SIZE);
		return this->freeMemory + (BLOCK_SIZE * (this->size - this->allocationStep));

	}
	return NULL;
}

void freeMemoryFromAllocator (struct MemoryAllocator* this, BLOCK_TYPE* memory)
{
#ifdef DEBUG
	printf ("<==freeMemoryFromAllocator\n");
	dumpMemoryAllocator (this, stdout);
#endif // DEBUG
	unsigned int offset = (memory - this->freeMemory) / BLOCK_SIZE;
#ifdef DEBUG
	printf ("memory offset = %u\n", offset);
#endif // DEBUG

	if (offset > this->size)
	{
		fprintf (stderr, "Incorrect offset, line = %d\n", __LINE__);
		return;
	}
	this->isFree[offset] = 1;
	this->freeSize ++;
	return;
}








