#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
    /* Функция сравнения двух struct point по расстоянию от начала координат*/
    int distance__1 = (((struct point*)__1)->x * ((struct point*)__1)->x) + (((struct point*)__1)->y * ((struct point*)__1)->y);
    int distance__2 = (((struct point*)__2)->x * ((struct point*)__2)->x) + (((struct point*)__2)->y * ((struct point*)__2)->y);
    return (distance__1 < distance__2) ? -1 : 1;
}


void merge_sort(void* Array, size_t size_of_array, size_t size_of_data, int (*compare_function)(const void*, const void*))
{
    if(size_of_array <= 1)
        return;
    else
    {
        void* Middle = Array + (size_of_array / 2) * size_of_data;
        void* End = Array + size_of_array * size_of_data;
        merge_sort((void*)Array  , size_of_array / 2                 , size_of_data, compare_function);
        merge_sort((void*)Middle , size_of_array - size_of_array / 2 , size_of_data, compare_function);
        void *buffer = malloc(size_of_array * size_of_data);
        void *first_iterator = Array, *second_iterator = Middle, *inserter = buffer;
        while((first_iterator < Middle) && (second_iterator < End))
        {
            if(compare_function(first_iterator, second_iterator) <= 0)
            {
                memcpy(inserter, first_iterator, size_of_data);
                first_iterator += size_of_data;
                inserter += size_of_data;
            }
            else
            {
                memcpy(inserter, second_iterator, size_of_data);
                second_iterator += size_of_data;
                inserter += size_of_data;
            }
        }
        while(first_iterator < Middle)
        {
            memcpy(inserter, first_iterator, size_of_data);
            first_iterator += size_of_data;
            inserter += size_of_data;
        }
        while(second_iterator < End)
        {
            memcpy(inserter, second_iterator, size_of_data);
            second_iterator += size_of_data;
            inserter += size_of_data;
        }
        memcpy(Array, buffer, size_of_array * size_of_data);
        free(buffer);
    }
}

int main(void)
{
    srand(time(0));
    int i;
/* сортируем целые числа */
    int a[N];
    for(i = 0; i < N; i++)
        a[i] = rand() % (2 * N);
    printf("Before: ");
    for(i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");
    merge_sort(a, N, sizeof(int), compare_int);
    printf("After: ");
    for(i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n\n");

/* сортируем точки по расстоянию до начала координат */
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
    merge_sort(b, N, sizeof(struct point), compare_point);
    printf("After: ");
    for(i = 0; i < N; i++)
        printf("(%d; %d) ", b[i].x, b[i].y);
    printf("\n\n");

    return 0;
}
