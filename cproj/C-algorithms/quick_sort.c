#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#define N 10

int compare_int(const void* __1, const void* __2)
{
    /* Функция сравнения двух int */
    return (*(int*)__1 < *(int*)__2) ? -1 : 1;
}

/* Структура, описывающая точку на плоскости */
struct point
{
    int x;
    int y;
};

int compare_point(const void* __1, const void* __2)
{
    /* Функция сравнения двух struct point по расстоянию от начала координат */
    int distance__1 = (((struct point*)__1)->x * ((struct point*)__1)->x) + (((struct point*)__1)->y * ((struct point*)__1)->y);
    int distance__2 = (((struct point*)__2)->x * ((struct point*)__2)->x) + (((struct point*)__2)->y * ((struct point*)__2)->y);
    return (distance__1 < distance__2) ? -1 : 1;
}

void swap_data(void* __1, void* __2, size_t size_of_data)
{
    size_t i = 0;
    for(i = 0; i < size_of_data; i++)
        *(uint8_t*)(__1 + i) ^= *(uint8_t*)(__2 + i);
    for(i = 0; i < size_of_data; i++)
        *(uint8_t*)(__2 + i) ^= *(uint8_t*)(__1 + i);
    for(i = 0; i < size_of_data; i++)
        *(uint8_t*)(__1 + i) ^= *(uint8_t*)(__2 + i);
}

void quick_sort(void* Array, size_t size_of_array, size_t size_of_data, int (*compare_function)(const void*, const void*))
{

    if(size_of_array <= 1)
        return;
    else
    {
        int i;
        for(i = 0; i < size_of_array; i++)
            printf("%d ", *((int*)(Array + size_of_data * i)));
        printf("\n");

        void* begin_iterator = Array;
        void* end_iterator = Array + (size_of_array - 1) * size_of_data;

        void* array_end = end_iterator;

        void* split_data = malloc(size_of_data);
        memcpy(split_data, begin_iterator, size_of_data);

        printf("begin = %d, end = %d, split = %d\n", *(int*)begin_iterator, *(int*)end_iterator, *(int*)split_data);
        while(begin_iterator < end_iterator)
        {
            while(compare_function(begin_iterator, split_data) < 0) begin_iterator += size_of_data;
            while(compare_function(end_iterator, split_data) > 0) end_iterator -= size_of_data;
            printf("begin = %d, end = %d\n", *(int*)begin_iterator, *(int*)end_iterator);
            if(begin_iterator < end_iterator)
            {
                printf("swap\n");
                swap_data(begin_iterator, end_iterator, size_of_data);
                begin_iterator += size_of_data;
                end_iterator -= size_of_data;
                for(i = 0; i < size_of_array; i++)
                    printf("%d ", *((int*)(Array) + i));
                printf("\n");
            }

        }

        free(split_data);

        printf("begin = %d, end = %d\n", *(int*)begin_iterator, *(int*)end_iterator);
        printf("---------------------------------\n");

        if(Array < end_iterator + size_of_data)
            quick_sort(Array, (end_iterator - Array) / size_of_data + 1, size_of_data, compare_function);

        if(begin_iterator + size_of_data < Array + size_of_array * size_of_data)
            quick_sort(begin_iterator, (size_of_array - 1) - (begin_iterator - Array) / size_of_data, size_of_data, compare_function);

    }
}

int main(void)
{
    srand(time(0));
    int i;
    /* сортируем целые числа */
    int a[N];
    for(i = 0; i < N; i++)
        a[i] = rand() % N + 1;
    printf("Before: ");
    for(i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");
    quick_sort(a, N, sizeof(int), compare_int);
    printf("After: ");
    for(i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n\n");

    return 0;
}
