#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/*��� ������������� INT_MAX � �������� �������������*/

#define DEBUG 0 /*����� ���������� � ���� ���������*/

int min(int x, int y)
/* ���������� �������� ���� ����� */
{
    return (x < y) ? x : y;
}
int main(void)
{
    if(DEBUG)
        freopen("input.txt", "r", stdin);
/*��� ������� ������������ ����� ����� �� ���������*/

    int n, m, i, j, begin, end, weight, start;
    scanf("%d %d", &n, &m);
/*��������� ����� ������ � ����� �����*/
    int** Graph = (int**)malloc(sizeof(int*) * n);
/*������� ������� ��������� �����*/
    if(Graph == NULL)
/*��������� ������ ��������� ������,
������� �������� �������������������*/
        return -1;
    for(i = 0; i < n; i++)
    {
        Graph[i] = (int*)calloc(n, sizeof(int));
/*calloc ��� ��������������� ��������� �������*/
        if(Graph[i] == NULL)
            return -1;
    }
    for(i = 0; i < m; i++)
    {
        scanf("%d %d %d", &begin, &end, &weight);
        if(Graph[begin][end] == 0) /*���� ����� ��� - �������*/
            Graph[begin][end] = weight;
        else
/*���� ����� ����� ��������� ���� ��������� �����,
 �� ������� �������� ������ ����������*/
            Graph[begin][end] = min(Graph[begin][end], weight);
/*��� ��� ���� �����������������,
 �� ������� ����� � � ������ �������*/
        if(Graph[end][begin] == 0)
            Graph[end][begin] = weight;
        else
            Graph[end][begin] = min(Graph[end][begin], weight);
    }
    scanf("%d", &start); /*��������� �������*/

    if(DEBUG)
/*������� ������������ �������*/
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

    int* Enabled = (int*)calloc(n, sizeof(int)); /*������� �� ���������� ������*/
    int* Dist = (int*)calloc(n, sizeof(int)); /*������ ����������*/
    for(i = 0; i < n; i++)
        Dist[i] = INT_MAX;

    Enabled[start] = 1;
    Dist[start] = 0;
    while(1)
    {
        int MinActive = -1; /* �������� ������� � ����������� Dist*/
        for(i = 0; i < n; i++)
            if(Enabled[i] && MinActive == -1)
                MinActive = i;
            else if(Enabled[i] && Dist[MinActive] > Dist[i])
                MinActive = i;

        if(DEBUG)
            printf("MinActive = %d\n", MinActive);

        if(MinActive == -1)
            break; /*�������� ������ �� �����, �������� ��������*/
        for(i = 0; i < n; i++)
            if(i != MinActive &&
               Graph[MinActive][i] &&
               Dist[i] > Dist[MinActive] + Graph[MinActive][i])
        /*���� ����� ��������� Dist[i] - ������ ���*/
            {
                Dist[i] = Dist[MinActive] + Graph[MinActive][i];
                Enabled[i] = 1; /*� ���������� ����������� �������*/
            }
        Enabled[MinActive] = 0;

        if(DEBUG) /*��������� Dist �� ������� ����*/
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
    for(i = 0; i < n; i++) /*������� �������� ���������*/
        printf("%d ", Dist[i]);
    /*������� ���������� ������*/
    for(i = 0; i < n; i++)
        free(Graph[i]);
    free(Graph);
    free(Enabled);
    free(Dist);
    return 0;
}