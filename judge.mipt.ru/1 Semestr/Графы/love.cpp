#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm> // ��� max
using namespace std;

int Edges_Count; // ���������� ������
map< string, set< string > > Graph; // ������
set< string > Names; // ������ ����
int Max_Len = 0; // ��������� ������ ���������
map< string, bool > Visited; // �������� �������, ���� ������� ����������� ���

////////////////////////////////////////////////////////////////////////////////////////////////////////

void DFS(string Current, set< string > Visited_Set, vector< string > Visited_Vector)
{

    // ��������� ������ � ������� ��� ���������� ���� ������ �����
    Visited[Current] = true;
    if(Visited_Set.find(Current) != Visited_Set.end())
    {
        // ������ � ��� ���������� ������� -> ���������� ����
        int Start = 0; // ����, ��� ����� �� � ���� ������� ����
        for(size_t i = 0; i < Visited_Vector.size(); i++)
        {
            if(Visited_Vector[i] == Current)
            {
                Start = i; // ��������
                break;
            }
        }
        // ��������� ���� �� ������������ (���������� ����������)
        bool Correct = true;
        // ���������� ����� ����� ��������� ����� (�������� ��������)
        int Edges = 0;
        for(size_t i = Start; i < Visited_Vector.size(); i++)
            for(size_t j = Start; j < Visited_Vector.size(); j++)
                if(  Graph[Visited_Vector[i]].find(Visited_Vector[j]) != Graph[Visited_Vector[i]].end() )
                    Edges++;
        // ���� ����� ������, ��� ������ � �����
        // �� ��������� �������� ���������        
        if(Edges != Visited_Vector.size() - Start )
            Correct = false;
        // ���� �������� ������ ������, �� ������������� ���������
        if(Correct)
            Max_Len = max(Max_Len, (int)(Visited_Vector.size() - Start));
    }
    else
    {
        // ����� ������ ������
        for(set< string >::iterator it = Graph[Current].begin(); it != Graph[Current].end(); it++)
        {
            set< string > New_Set = Visited_Set;
            vector< string > New_Vector = Visited_Vector;
            New_Set.insert(Current);
            New_Vector.push_back(Current);
            DFS(*it, New_Set, New_Vector);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    //freopen("input.txt", "r", stdin);

    cin >> Edges_Count;
    string s1, s2;
    for(size_t i = 0; i < Edges_Count; i++)
    {
        cin >> s1 >> s2;
        Graph[s1].insert(s2);
        Names.insert(s1);
        Names.insert(s2);
    }

    for(set<string>::iterator it = Names.begin(); it != Names.end(); it++)
    {
        // ���� �� �� ������������� ���, ��� ���� ���� �������
        if(!Visited[*it])
            DFS(*it, set<string>(), vector<string>());
    }



    cout << (Max_Len > 2 ? Max_Len : 0);
    return 0;
}