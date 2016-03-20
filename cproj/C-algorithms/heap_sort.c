#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#define N 500

int compare_int(const void* __1, const void* __2)
{
    /* Функция сравнения двух int */
    return (*(int*)__1 - *(int*)__2);
}

/* Структура, описывающая точку на плоскости */
struct point
{
    int x;
    int y;
};

int compare_point(const void* __1, const void* __2)
{
    /* Функция сравнения двух struct point по расстоянию от начала координат*/
    int distance__1 = (((struct point*)__1)->x * ((struct point*)__1)->x) + (((struct point*)__1)->y * ((struct point*)__1)->y);
    int distance__2 = (((struct point*)__2)->x * ((struct point*)__2)->x) + (((struct point*)__2)->y * ((struct point*)__2)->y);
    return (distance__1 < distance__2) ? -1 : 1;
}

inline void swap_data(void* __1, void* __2, size_t size_of_data)
{
    size_t i = 0;
    for(i = 0; i < size_of_data; i++)
    {
        *(uint8_t*)(__1 + i) ^= *(uint8_t*)(__2 + i);
        *(uint8_t*)(__2 + i) ^= *(uint8_t*)(__1 + i);
        *(uint8_t*)(__1 + i) ^= *(uint8_t*)(__2 + i);
    }
}

void heap_sort(void* Array, size_t size_of_array, size_t size_of_data, int (*compare_function)(const void*, const void*))
{
    void* heap = malloc(size_of_array * size_of_data);
    memcpy(heap, Array, size_of_data * size_of_array);
    int heap_size = 0, current_index;
    for(heap_size = 0; heap_size < size_of_array; heap_size++)
    {
        int current_index = heap_size;
        while(current_index > 0 && compare_function(heap + size_of_data * current_index, heap + size_of_data * ((current_index - 1) / 2)) < 0)
        {
            swap_data(heap + size_of_data * current_index, heap + size_of_data * ((current_index - 1) / 2), size_of_data);
            current_index = (current_index - 1) / 2;
        }
    }
    int fill_index = 0;
    void* min_buffer = malloc(size_of_data);
    for(fill_index = 0; fill_index < size_of_array; fill_index++)
    {
        memcpy(Array + fill_index * size_of_data, heap, size_of_data);
        memcpy(heap, heap + (heap_size - 1) * size_of_data, size_of_data);
        heap_size--;
        current_index = 0;
        while(current_index < heap_size)
        {
            memcpy(min_buffer, heap + current_index * size_of_data, size_of_data);

            if(current_index * 2 + 1 < heap_size)
                if(compare_function( min_buffer, heap + (current_index * 2 + 1) * size_of_data ) > 0)
                    memcpy(min_buffer, heap + (current_index * 2 + 1) * size_of_data, size_of_data);
            if(current_index * 2 + 2 < heap_size)
                if(compare_function( min_buffer, heap + (current_index * 2 + 2) * size_of_data ) > 0)
                    memcpy(min_buffer, heap + (current_index * 2 + 2) * size_of_data, size_of_data);

            if(memcmp( min_buffer, heap + current_index * size_of_data, size_of_data ) == 0)
                break;
            else if(memcmp( min_buffer, heap + (current_index * 2 + 1) * size_of_data, size_of_data ) == 0)
            {
                swap_data(heap + current_index * size_of_data, heap + (current_index * 2 + 1) * size_of_data, size_of_data);
                current_index = current_index * 2 + 1;
            }
            else if(memcmp( min_buffer, heap + (current_index * 2 + 2) * size_of_data, size_of_data ) == 0)
            {
                swap_data(heap + current_index * size_of_data, heap + (current_index * 2 + 2) * size_of_data, size_of_data);
                current_index = current_index * 2 + 2;
            }
        }
    }
    free(min_buffer);
    free(heap);

}

int main(void)
{

    srand(time(0));
    int i;

    int a[N];
    int b[N];
    int c[N];
    int j;
    for(j = 0; j < 1000; j++)
    {
        for(i = 0; i < N; i++)
            a[i] = rand() % (2 * N);
        memcpy(b, a, sizeof(int) * N);
        memcpy(c, a, sizeof(int) * N);
        qsort(b, N, sizeof(int), compare_int);
        heap_sort(c, N, sizeof(int), compare_int);
        if(memcmp(b, c, sizeof(int) * N) == 0)
        {
            printf("-----  ");
        }
        else
        {
            printf("BAD!   ");
        }
        if(j % 15 == 14)
            printf("\n");

    }


    /* сортируем точки по расстоянию до начала координат
        struct point b[N];
        for(i = 0; i < N; i++)
        {
            b[i].x = rand() % (2 * N) - rand() % N;
            b[i].y = rand() % (2 * N) - rand() % N;;
        }
        printf("Before: ");
        for(i = 0; i < N; i++)
            printf("(%d; %d) ", b[i].x, b[i].y);
        printf("\n");
        heap_sort(b, N, sizeof(struct point), compare_point);
        printf("After: ");
        for(i = 0; i < N; i++)
            printf("(%d; %d) ", b[i].x, b[i].y);
        printf("\n\n");
    */
    return 0;
}
