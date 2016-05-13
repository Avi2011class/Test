#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/*Для использования INT_MAX в качестве бесконечности*/

#define DEBUG 0 /*Вывод информации о ходе выполения*/

int min(int x, int y)
/* Вычисление минимума двух целых */
{
    return (x < y) ? x : y;
}
int main(void)
{
    if(DEBUG)
        freopen("input.txt", "r", stdin);
/*Для отладки перенаправим поток ввода на заготовку*/

    int n, m, i, j, begin, end, weight, start;
    scanf("%d %d", &n, &m);
/*Считываем число вершин и ребер графа*/
    int** Graph = (int**)malloc(sizeof(int*) * n);
/*Создаем матрицу смежности графа*/
    if(Graph == NULL)
/*Обработка ошибок выделения памяти,
немного жертвуем производительностью*/
        return -1;
    for(i = 0; i < n; i++)
    {
        Graph[i] = (int*)calloc(n, sizeof(int));
/*calloc для автоматического обнуления матрицы*/
        if(Graph[i] == NULL)
            return -1;
    }
    for(i = 0; i < m; i++)
    {
        scanf("%d %d %d", &begin, &end, &weight);
        if(Graph[begin][end] == 0) /*Если ребра нет - добавим*/
            Graph[begin][end] = weight;
        else
/*если между двумя вершинами идет несколько ребер,
 то логично оставить только наименьшее*/
            Graph[begin][end] = min(Graph[begin][end], weight);
/*Так как граф неориентированный,
 то добавим ребро и в другую сторону*/
        if(Graph[end][begin] == 0)
            Graph[end][begin] = weight;
        else
            Graph[end][begin] = min(Graph[end][begin], weight);
    }
    scanf("%d", &start); /*Начальная вершина*/

    if(DEBUG)
/*Покажем составленную матрицу*/
    {
        printf("Graph:\n   ");
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
                printf("%3d ", Graph[i][j]);
            printf("\n   ");
        }
        printf("\n");
        printf("Start = %d\n-----------------------------------------------\n", start);
    }

    int* Enabled = (int*)calloc(n, sizeof(int)); /*Отметки об активности вершин*/
    int* Dist = (int*)calloc(n, sizeof(int)); /*Массив расстояний*/
    for(i = 0; i < n; i++)
        Dist[i] = INT_MAX;

    Enabled[start] = 1;
    Dist[start] = 0;
    while(1)
    {
        int MinActive = -1; /* активная вершина с минимальным Dist*/
        for(i = 0; i < n; i++)
            if(Enabled[i] && MinActive == -1)
                MinActive = i;
            else if(Enabled[i] && Dist[MinActive] > Dist[i])
                MinActive = i;

        if(DEBUG)
            printf("MinActive = %d\n", MinActive);

        if(MinActive == -1)
            break; /*Активных вершин не нашли, алгоритм закончен*/
        for(i = 0; i < n; i++)
            if(i != MinActive &&
               Graph[MinActive][i] &&
               Dist[i] > Dist[MinActive] + Graph[MinActive][i])
        /*Если можно уменьшить Dist[i] - делаем это*/
            {
                Dist[i] = Dist[MinActive] + Graph[MinActive][i];
                Enabled[i] = 1; /*и активируем уменьшенную вершину*/
            }
        Enabled[MinActive] = 0;

        if(DEBUG) /*Состояние Dist на текущем шаге*/
        {
            printf("   Dist: ");
            for(i = 0; i < n; i++)
                if(Dist[i] != INT_MAX)
                    printf("%d:%d  ", i, Dist[i]);
                else
                    printf("%d:inf  ", i);
            printf("\n\n");
        }
    }
    if(DEBUG)
        printf("--------------------------------------\n");
    for(i = 0; i < n; i++) /*Выводим конечный результат*/
        printf("%d ", Dist[i]);
    /*Очищаем выделенную память*/
    for(i = 0; i < n; i++)
        free(Graph[i]);
    free(Graph);
    free(Enabled);
    free(Dist);
    return 0;
}