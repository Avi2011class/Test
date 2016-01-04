#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define N 9
#define K 3
#define DEBUG 0
#define USEALLOCATOR 1
struct Cell
{
    size_t i;
    size_t j;
    int Can[N + 1];
    int Var;
};
struct MemoryAllocator
{
    int Size;
    int SizeStep;
    int FreeCount;
    int* CanBeUsed;
    int*** FreeMemory;
};
struct MemoryAllocator* CreateMemoryAllocator(int AllocatorStep)
{
    size_t i, j, k;
    struct MemoryAllocator* NewAllocator = (struct MemoryAllocator*)malloc(sizeof(struct MemoryAllocator));
    NewAllocator->Size = AllocatorStep;
    NewAllocator->SizeStep = AllocatorStep;
    NewAllocator->FreeCount = AllocatorStep;
    NewAllocator->CanBeUsed = (int*)malloc(sizeof(int) * AllocatorStep);
    for(i = 0; i < AllocatorStep; i++)
        NewAllocator->CanBeUsed[i] = 1;
    NewAllocator->FreeMemory = (int***)malloc(sizeof(int**) * AllocatorStep);
    for(i = 0; i < AllocatorStep; i++)
    {
        NewAllocator->FreeMemory[i] = (int**)calloc(N, sizeof(int*));
        for(j = 0; j < N; j++)
            NewAllocator->FreeMemory[i][j] = (int*)calloc(N, sizeof(int));
    }
    return NewAllocator;
};
int** GetMemory(struct MemoryAllocator* Allocator)
{
    if(DEBUG)
    {
        size_t iter;
        printf("\nGetMemoryStart\n");
        printf("Allocator params: \n  Size=%d  SizeStep=%d  FreeCount=%d\n", Allocator->Size, Allocator->SizeStep, Allocator->FreeCount);
        printf("  CanBeUsed & FreeMemory:\n      ");
        for(iter = 0; iter < Allocator->Size; iter++)
        {
            printf("x%03d: %d :x%09lld   ", iter, Allocator->CanBeUsed[iter], (long long int)Allocator->FreeMemory[iter]);
            if(iter % Allocator->SizeStep == Allocator->SizeStep - 1)
                printf("\n      ");
        }
    }
    if(Allocator->FreeCount > 0)
    {
        size_t iter;
        for(iter = 0; iter < Allocator->Size; iter++)
            if(Allocator->CanBeUsed[iter])
            {
                Allocator->CanBeUsed[iter] = 0;
                Allocator->FreeCount--;
                if(DEBUG) printf("GetMemoryEnd1\n");
                return Allocator->FreeMemory[iter];
            }
    }
    else
    {
        size_t iter, j;
        Allocator->FreeCount += Allocator->SizeStep - 1;
        Allocator->CanBeUsed = (int*)realloc(Allocator->CanBeUsed, sizeof(int) * (Allocator->Size + Allocator->SizeStep));
        Allocator->FreeMemory = (int***)realloc(Allocator->FreeMemory, sizeof(int**) * (Allocator->Size + Allocator->SizeStep));
        for(iter = Allocator->Size; iter < Allocator->Size + Allocator->SizeStep; iter++)
        {
            Allocator->FreeMemory[iter] = (int**)calloc(N, sizeof(int*));
            for(j = 0; j < N; j++)
                Allocator->FreeMemory[iter][j] = (int*)calloc(N, sizeof(int));
            Allocator->CanBeUsed[iter] = 1;
        }
        Allocator->Size += Allocator->SizeStep;

        if(DEBUG) printf("GetMemoryEnd2\n");
        Allocator->CanBeUsed[Allocator->Size - Allocator->SizeStep] = 0;
        return Allocator->FreeMemory[Allocator->Size - Allocator->SizeStep];
    }
    if(DEBUG) printf("GetMemoryEnd3\n");
    return NULL;
}
int FreeMemory(struct MemoryAllocator* Allocator, int** Memory)
{
    if(DEBUG)
    {
        size_t iter;
        printf("\nFreeMemoryStart\n");
        printf("  Memory=x%09lld\n", (long long int)Memory);
        printf("  Allocator params: \n  Size=%d  SizeStep=%d  FreeCount=%d\n", Allocator->Size, Allocator->SizeStep, Allocator->FreeCount);
        printf("    CanBeUsed & FreeMemory:\n      ");
        for(iter = 0; iter < Allocator->Size; iter++)
        {
            printf("x%03d: %d :x%09lld   ", iter, Allocator->CanBeUsed[iter], (long long int)Allocator->FreeMemory[iter]);
            if(iter % Allocator->SizeStep == Allocator->SizeStep - 1)
                printf("\n      ");
        }
        printf("\n");
    }

    size_t iter, j;
    for(iter = 0; iter < Allocator->Size; iter++)
        if(Allocator->FreeMemory[iter] == Memory)
        {
            if(DEBUG)
            {
                printf("  Found: %d\n", iter);
                printf("  CanBeUsed[%d]=%d\n", iter, Allocator->CanBeUsed[iter]);
                if( Allocator->CanBeUsed[iter] == 1)
                    exit(0);
            }
            for(j = 0; j < N; j++)
                memset(Memory[j], 0, N);

            Allocator->CanBeUsed[iter] = 1;
            Allocator->FreeCount++;
            return 1;
        }
    return 0;
}
void DestroyMemoryAllocator(struct MemoryAllocator* Allocator)
{
    size_t iter, j;
    free(Allocator->CanBeUsed);
    for(iter = 0; iter < Allocator->Size; iter++)
    {
        for(j = 0; j < N; j++)
            free(Allocator->FreeMemory[iter][j]);
        free(Allocator->FreeMemory[iter]);
    }
    free(Allocator);
}
int** CreateArray(struct MemoryAllocator* Allocator)
{
    if(USEALLOCATOR == 0)
    {
        size_t i;
        int** NewArray = (int**)calloc(N, sizeof(int*));
        for(i = 0; i < N; i++)
            NewArray[i] = (int*)calloc(N, sizeof(int));
        return NewArray;
    }
    else
        return GetMemory(Allocator);
    return NULL;
}
int** CopyArray(int** From, int** To)
{
    size_t i, j;
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            To[i][j] = From[i][j];
}
void DestroyArray(struct MemoryAllocator* Allocator, int** Array)
{
    if(USEALLOCATOR == 0)
    {
        size_t i;
        for(i = 0; i < N; i++)
            free(Array[i]);
        free(Array);
    }
    else
        FreeMemory(Allocator, Array);
}
int FScanfArray(int** Array, const char* File)
{
    FILE* Input = fopen(File, "r");
    if(Input == NULL)
        return 0;
    size_t i, j;
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
        {
            if(fscanf(Input, "%d", &(Array[i][j])) <= 0)
                return 0;
        }
    close(Input);
    return 1;
}
void PrintfArray(int** Array)
{
    size_t i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            if(Array[i][j] > 0)
                printf("%d ", Array[i][j]);
            else
                printf("- ");
            if(j % K == K - 1)
                printf("  ");
        }
        printf("\n");
        if(i % K == K - 1)
            printf("\n");
    }
    printf("/////////////////////\n");
}
struct Cell CalcField(int** From) /* */
{
    size_t i, j;
    size_t ki, kj, iter;

    struct Cell Result, Tmp;
    Result.Var = 10;

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            if(From[i][j] == 0)
            {

                Tmp.i = i;
                Tmp.j = j;
                for(iter = 0; iter < N + 1; iter++)
                    Tmp.Can[iter] = 1;
                Tmp.Var = 9;

                for(kj = 0; kj < N; kj++)
                    Tmp.Can[From[i][kj]] = 0;

                for(ki = 0; ki < N; ki++)
                    Tmp.Can[From[ki][j]] = 0;

                for(ki = i - (i % K); ki < i + K - (i % K); ki++)
                    for(kj = j - (j % K); kj < j + K - (j % K); kj++)
                        Tmp.Can[From[ki][kj]] = 0;

                for(iter = 1; iter < N + 1; iter++)
                    if(!Tmp.Can[iter])
                        Tmp.Var--;

                if(Tmp.Var < Result.Var)
                    Result = Tmp;
            }
    return Result;
}
int ArrayIsFull(int** Array)
{
    size_t i, j;
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            if(Array[i][j] == 0)
                return 0;
    return 1;
}
int RecursionStep(int** Field, struct MemoryAllocator* Allocator)
{
    if(ArrayIsFull(Field))
        return 1;

    struct Cell Next = CalcField(Field);
    if(Next.Var == 0)
        return 0;

    int** Backup = CreateArray(Allocator);
    CopyArray(Field, Backup);

    size_t k;
    for(k = 1; k < N + 1; k++)
        if(Next.Can[k])
        {
            Field[Next.i][Next.j] = k;
            if(RecursionStep(Field, Allocator))
            {
                DestroyArray(Allocator, Backup);
                return 1;
            }
            CopyArray(Backup, Field);
        }
    DestroyArray(Allocator, Backup);
    return 0;
}
int main(void)
{
    /*if(DEBUG)
        freopen("ERRLOG.txt", "w", stdout);*/
    system("COLOR 0E");
    setlocale(LC_ALL, "rus");
    struct MemoryAllocator* Allocator = CreateMemoryAllocator(5);

    int** Field = CreateArray(Allocator);

    if(!FScanfArray(Field, "input.txt"))
    {
        printf("Ошибка при открытии файла или считывании\n");
        return 0;
    }
    PrintfArray(Field);

    if(RecursionStep(Field, Allocator))
    {
        printf("Судоку решен\n");
        PrintfArray(Field);
    }
    else
    {
        printf("Решений нет\n");
    }

    DestroyArray(Allocator, Field);
    DestroyMemoryAllocator(Allocator);
    return 0;
}
