#include <iostream>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <locale.h>
#include <ctime>
#include <algorithm>
#include <vector>
#include <climits>
#include <stack>
#include <queue>

#define SS 10
using namespace std;
/////////////////////////////////////////////////////////
HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024
    HWND hwndFound;
    char pszNewWindowTitle[MY_BUFSIZE];
    char pszOldWindowTitle[MY_BUFSIZE];
    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
    wsprintf(pszNewWindowTitle,"%d/%d", GetTickCount(), GetCurrentProcessId());
    SetConsoleTitle(pszNewWindowTitle);
    Sleep(40);
    hwndFound = FindWindow(NULL, pszNewWindowTitle);
    SetConsoleTitle(pszOldWindowTitle);
    return(hwndFound);
}
/////////////////////////////////////////////
struct Square
{
    bool Up, Left, Enabled;
    int Up_Weight = 0, Left_Weight = 0;
    void draw(HDC hDC, int m, int n)
    {
        if(Up) {
            MoveToEx(hDC, 20 + SS * n, 20 + SS * m, 0);
            LineTo(hDC, 20 + SS * (n + 1), 20 + SS * m);
        }
        if(Left) {
            MoveToEx(hDC, 20 + SS * n, 20 + SS * m, 0);
            LineTo(hDC, 20 + SS * n, 20 + SS * (m + 1));
        }
    }
    void fill(HDC hDC, int m, int n)
    {
        Rectangle(hDC, 20 + SS * n, 20 + SS * m, 20 + SS * (n + 1), 20 + SS * (m + 1));
    }

};

vector<vector<Square> > Create_Field(HDC hDC, int Height, int Width)
{
    vector< vector<Square> > Tmp_Field;
    Tmp_Field.resize(Height);
    for(size_t i = 0; i < Height; i++) Tmp_Field[i].resize(Width);
    for(size_t i = 0; i < Height; i++)
        for(size_t j = 0; j < Width; j++)
        {
            Tmp_Field[i][j].Left = true;
            Tmp_Field[i][j].Up = true;
            Tmp_Field[i][j].Enabled = false;
            Tmp_Field[i][j].Left_Weight = rand();
            Tmp_Field[i][j].Up_Weight = rand();
        }


    for(size_t k = 0; k < Height * Width; k++) // осн цикл
    {
        int MinLeft = INT_MAX;
        int MinUp = INT_MAX;
        int IU = 0, JU = 0, IL = 0, JL = 0;
        Tmp_Field[0][0].Enabled = true;
        for(size_t i = 0; i < Height; i++) for(size_t j = 0; j < Width; j++)
        {
            if(i > 0)
                if((Tmp_Field[i][j].Enabled ^ Tmp_Field[i - 1][j].Enabled) && (MinUp > Tmp_Field[i][j].Up_Weight))
                {
                    MinUp = Tmp_Field[i][j].Up_Weight;
                    IU = i; JU = j;
                }
            if(j > 0)
                if((Tmp_Field[i][j].Enabled ^ Tmp_Field[i][j - 1].Enabled) && (MinLeft > Tmp_Field[i][j].Left_Weight))
                {
                    MinLeft = Tmp_Field[i][j].Left_Weight;
                    IL = i; JL = j;
                }
        }
        if(MinLeft < MinUp)
        {
            Tmp_Field[IL][JL].Enabled = true;
            Tmp_Field[IL][JL - 1].Enabled = true;
            Tmp_Field[IL][JL].Left = false;
        }
        else if(MinLeft > MinUp)
        {
            Tmp_Field[IU][JU].Enabled = true;
            Tmp_Field[IU - 1][JU].Enabled = true;
            Tmp_Field[IU][JU].Up = false;
        }
        else if(MinLeft != INT_MAX)
        {
            Tmp_Field[IL][JL].Enabled = true;
            Tmp_Field[IL][JL - 1].Enabled = true;
            Tmp_Field[IL][JL].Left = false;
        }

    }
    /*for(size_t k = 0; k < 10 * Height; k++)
    {
        int i0, j0;
        i0 = rand() % Height; j0 = rand() % Height;
        Tmp_Field[i0][j0].Up = false;
        i0 = rand() % Height; j0 = rand() % Height;
        Tmp_Field[i0][j0].Left = false;
    }//*/
    for(size_t i = 0; i < Height; i++) for(size_t j = 0; j < Width; j++)
        Tmp_Field[i][j].draw(hDC, i, j);


    MoveToEx(hDC, 20, 20, 0);
    LineTo(hDC, 20, 20 + SS * Width);
    LineTo(hDC, 20 + SS * Height, 20 + SS * Width);
    LineTo(hDC, 20 + SS * Height, 20);
    LineTo(hDC, 20, 20);
    return Tmp_Field;
}
////////////////////////////////////////////////////
void DrawBFS(vector<vector<Square> > Cur, int Height, int Width)
{
    HWND Hwnd = GetConsoleHwnd();
    HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HDC hDC = GetDC(Hwnd);
    HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 200));
    SelectObject(hDC, hBlackBrush);
    SelectObject(hDC, Pen);
    for(size_t i = 0; i < Height; i++) for(size_t j = 0; j < Width; j++)
        Cur[i][j].Enabled = false;
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));
    while(q.size() > 0)
    {
        pair<int, int> now = q.front(); q.pop();
        Cur[now.first][now.second].fill(hDC, now.first, now.second);
        if(now.first > 0) //up
            if((!Cur[now.first - 1][now.second].Enabled) && !Cur[now.first][now.second].Up)
            {
                Cur[now.first - 1][now.second].Enabled = true;
                q.push(make_pair(now.first - 1, now.second));
            }
        if(now.first < Height - 1) //down
            if((!Cur[now.first + 1][now.second].Enabled) && !Cur[now.first + 1][now.second].Up)
            {
                Cur[now.first + 1][now.second].Enabled = true;
                q.push(make_pair(now.first + 1, now.second));
            }
        if(now.second > 0) //left
            if((!Cur[now.first][now.second - 1].Enabled) && !Cur[now.first][now.second].Left)
            {
                Cur[now.first ][now.second - 1].Enabled = true;
                q.push(make_pair(now.first, now.second - 1));
            }
        if(now.second < Width - 1) //right
            if((!Cur[now.first][now.second + 1].Enabled) && !Cur[now.first][now.second + 1].Left)
            {
                Cur[now.first][now.second + 1].Enabled = true;
                q.push(make_pair(now.first, now.second + 1));
            }
        int h = 0;
        while(h < 100000) { cout << 1; h++;}
        int j = h;
        //Sleep(6);
    }
    ReleaseDC(Hwnd, hDC);
}
//////////////////////////////////////////////
int main()
{
    freopen("input.txt", "w", stdout);
    int n = 70;
    srand(time(0));
    setlocale(LC_ALL, "rus");
    HWND Hwnd = GetConsoleHwnd();
    HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    HDC hDC = GetDC(Hwnd);
    HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 100));
    SelectObject(hDC, hBlackBrush);
    SelectObject(hDC, Pen);
    vector< vector<Square> > Cur = Create_Field(hDC, n, n);
    DrawBFS(Cur, n, n);
    ReleaseDC(Hwnd, hDC);
    return 0;
}
