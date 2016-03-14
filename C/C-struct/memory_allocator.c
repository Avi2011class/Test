#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DEBUG 0

struct MemoryAllocator {
	int BlockSize;
	int AllocatorSize;
	int AllocatorStep;
	int FreeCount;
	int *CanBeUsed;
	void **FreeMemory;
};

struct MemoryAllocator *CreateMemoryAllocator(int BlockSize, int AllocatorStep)
{
	int i;
	struct MemoryAllocator *NewAllocator =
	    (struct MemoryAllocator *)malloc(sizeof(struct MemoryAllocator));
	if (NewAllocator == NULL)
		return NULL;
	NewAllocator->BlockSize = BlockSize;
	NewAllocator->AllocatorSize = AllocatorStep;
	NewAllocator->FreeCount = AllocatorStep;
	NewAllocator->AllocatorStep = AllocatorStep;
	NewAllocator->CanBeUsed = (int *)malloc(sizeof(int) * AllocatorStep);
	if (NewAllocator->CanBeUsed == NULL)
		return NULL;
	NewAllocator->FreeMemory =
	    (void **)malloc(sizeof(void *) * AllocatorStep);
	if (NewAllocator->FreeMemory == NULL)
		return NULL;
	for (i = 0; i < AllocatorStep; i++) {
		NewAllocator->CanBeUsed[i] = 1;
		NewAllocator->FreeMemory[i] =
		    (void *)malloc((size_t) BlockSize);
		if (NewAllocator->FreeMemory[i] == NULL)
			return NULL;
		memset(NewAllocator->FreeMemory[i], 0, BlockSize);
	}
	return NewAllocator;
}

void *GetMemoryFromAllocator(struct MemoryAllocator *Allocator)
{
	if (Allocator->FreeCount > 0) {
		int iterator;
		for (iterator = 0; iterator < Allocator->AllocatorSize;
		     iterator++)
			if (Allocator->CanBeUsed[iterator]) {
				Allocator->CanBeUsed[iterator] = 0;
				Allocator->FreeCount--;
				return Allocator->FreeMemory[iterator];
			}
	} else {
		int iterator;

		int *NewCanBeUsed = (int *)realloc(Allocator->CanBeUsed,
						   sizeof(int) *
						   (Allocator->AllocatorSize +
						    Allocator->AllocatorStep));
		if (NewCanBeUsed == NULL)
			return NULL;
		Allocator->CanBeUsed = NewCanBeUsed;

		void **NewFreeMemory = (void **)realloc(Allocator->FreeMemory,
							sizeof(void *) *
							(Allocator->AllocatorSize
							 +
							 Allocator->AllocatorStep));
		if (NewFreeMemory == NULL)
			return NULL;
		Allocator->FreeMemory = NewFreeMemory;
		for (iterator = Allocator->AllocatorSize;
		     iterator <
		     Allocator->AllocatorSize + Allocator->AllocatorStep;
		     iterator++) {
			Allocator->FreeMemory[iterator] =
			    (void *)calloc(1, Allocator->BlockSize);
			if (Allocator->FreeMemory[iterator] == NULL)
				return NULL;
			Allocator->CanBeUsed[iterator] = 1;
		}
		Allocator->CanBeUsed[Allocator->AllocatorSize] = 0;
		Allocator->AllocatorSize += Allocator->AllocatorStep;
		Allocator->FreeCount += Allocator->AllocatorStep - 1;
		return Allocator->FreeMemory[Allocator->AllocatorSize -
					     Allocator->AllocatorStep];
	}
	return NULL;
}

int FreeMemoryInAllocator(struct MemoryAllocator *Allocator, void *Memory)
{
	int iterator;
	for (iterator = 0; iterator < Allocator->AllocatorSize; iterator++)
		if (Allocator->FreeMemory[iterator] == Memory
		    && Allocator->CanBeUsed[iterator] == 0) {
			Allocator->CanBeUsed[iterator] = 1;
			Allocator->FreeCount++;
			memset(Allocator->FreeMemory[iterator], 0,
			       Allocator->BlockSize);
			return 1;
		}
	return 0;
}

void DestroyMemoryAllocator(struct MemoryAllocator *Allocator)
{
	int iterator;
	for (iterator = 0; iterator < Allocator->AllocatorSize; iterator++)
		free(Allocator->FreeMemory[iterator]);
	free(Allocator->CanBeUsed);
	free(Allocator->FreeMemory);
	free(Allocator);
}

void PrintfMemoryAllocatorInfo(struct MemoryAllocator *Allocator)
{
	printf("MemoryAllocator dump: %9lld\n", (long long int)Allocator);
	printf
	    ("    AllocatorSize: %d\n    Allocator FreeCount: %d\n    AllocatorStep: %d\n",
	     Allocator->AllocatorSize, Allocator->FreeCount,
	     Allocator->AllocatorStep);
	printf("    FreeMemory:");
	int iterator;
	for (iterator = 0; iterator < Allocator->AllocatorSize; iterator++) {
		if (iterator % 5 == 0)
			printf("\n    ");
		printf("%3d_:%d:_%9lld       ", iterator,
		       Allocator->CanBeUsed[iterator],
		       (long long int)Allocator->FreeMemory[iterator]);
	}
	printf("\n---------------------------------------------------\n");
}

int main(void)
{
	struct MemoryAllocator *A = CreateMemoryAllocator(1024 * 1024, 4);
	PrintfMemoryAllocatorInfo(A);
	int n = 10000;
	void **arr = (void **)malloc(sizeof(void *) * n);
	int i;
	double Time = clock();

	for (i = 0; i < n; i++) {
		arr[i] = GetMemoryFromAllocator(A);
		/* PrintfMemoryAllocatorInfo(A); */
	}
	for (i = 0; i < n; i++) {
		FreeMemoryInAllocator(A, arr[i]);
		/* PrintfMemoryAllocatorInfo(A); */
	}
	free(arr);

	DestroyMemoryAllocator(A);
	Time = Time - clock();
	printf("WorkTie = %lg\n", Time / CLOCKS_PER_SEC);
	return 0;
}
