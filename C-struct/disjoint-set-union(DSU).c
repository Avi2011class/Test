#include <stdio.h>
#include <stdlib.h>


/*
������� ���������������� ��������
� ������ ������ ��������������� ��������� ������ "������� ���������������� ��������" 
(�� ���������� "disjoint-set-union", ��� ������ "DSU").

��� ��������� ������ ������������� ��������� �����������.'
' ���������� ������� ��������� ���������, ������ �� ������� ��������� � ��������� 
(���� �����������) ���������. �� ���� �������� ����� ���������� ��� �����-���� ���������,
 � ����� ����� ���������, � ����� ��������� ������ ��������� ��������� �������. 
 �����, � ������������ ��������, �������� ��� ���� �������� � �������� ������ ��������, 
 ������� ���������� � ��������� ���������.

����� �������, ������� ��������� ������ ��������� ������ ������� ����� �� ��� ��������:

{\rm make\_set}(x) � ��������� ����� ������� x, ������� ��� � ����� ���������, ��������� �� ������ ����.
{\rm union\_sets}(x,y) � ���������� ��� ��������� ��������� 
(���������, � ������� ��������� ������� x, � ���������, � ������� ��������� ������� y).
{\rm find\_set}(x) � ����������, � ����� ��������� ��������� ��������� ������� x.
 �� ����� ���� ��� ���� ������������ ���� �� ��������� ��������� (���������� �������������� 
 ��� ������� (� ������������ ���������� "leader")). ���� ������������� ���������� �
 ������ ��������� ����� ���������� ������ (� ����� �������� � �������� �������, � ������,
 ����� ������� {\rm union\_sets}()).
*/


/*---------------DSU--------------------------*/
struct DSU
{
    int* Parent;
    int* Range;
    int Length;
};
struct DSU* DSU_Init(int Count);
void DSU_MakeNewSet(struct DSU* D, int V);
int DSU_FindSet(struct DSU* D, int V);
void DSU_UnionSets(struct DSU* D, int X, int Y);
/*---------------------------------------------*/
struct DSU* DSU_Init(int Count)
{
    struct DSU* D = (struct DSU*)malloc(sizeof(struct DSU));
    D->Parent = (int*)malloc(Count * sizeof(int));
    D->Range = (int*)malloc(Count * sizeof(int));

    int i = 0;
    for(i = 0; i < Count; i++)
    {
        D->Parent[i] = -1;
        D->Range[i] = 0;
    }
    D->Length = Count;
    return D;
}
void DSU_MakeNewSet(struct DSU* D, int V)
{
    D->Parent[V] = V;
    D->Range[V] = 1;
}
int DSU_FindSet(struct DSU* D, int V)
{
    if(D->Parent[V] == V)
        return V;
    else
    {
        D->Parent[V] = DSU_FindSet(D, D->Parent[V]);
        return D->Parent[V];
    }

}
void DSU_UnionSets(struct DSU* D, int X, int Y)
{
    X = DSU_FindSet(D, X);
	Y = DSU_FindSet(D, Y);
	if (X != Y)
    {
        if (D->Range[X] < D->Range[Y])
        {
            int Buf = X;
            X = Y;
            Y = Buf;
        }
		D->Parent[Y] = X;
		D->Range[X] += D->Range[Y];
    }
}
/*---------------------------------------------*/
int main(void)
{
    return 0;
}
