#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>

#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <tchar.h>
#include <E:\\флешка\\проги\\3D++\\3D.h>
#include <thread>
#include <chrono>

using namespace std;

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
    hwndFound=FindWindow(NULL, pszNewWindowTitle);
    SetConsoleTitle(pszOldWindowTitle);
    return(hwndFound);
}
long double t = 1;
inline double f(double x, double y)
{
    //x = x / 1.5; y = y / 1.5;
    return      exp(-sqrt((x) * (x) + y * y) / 120 + 3.3) * cos(-t + sqrt((x) * (x) + y * y) / 10);
               // exp(-sqrt((x - 50) * (x - 50) + y * y) / 120 + 3.3) * cos(-t + sqrt((x - 50) * (x - 50) + y * y) / 10);
    //exp(-sqrt((x) * (x) + (y - 100) * (y - 100)) / 100 + 3) * cos(-t + 4 + sqrt((x) * (x) + (y - 100) * (y - 100)) / 10) +
    //exp(-sqrt((x) * (x) + (y + 100) * (y + 100)) / 100 + 3) * cos(-t + 2 + sqrt((x) * (x) + (y + 100) * (y + 100)) / 10);;
    ;
}
inline double g(double x, double y)
{

    return (x*x + y*y < 20000) ? sqrt(20000 - x*x - y*y) : 0;

}
int main()
{
    setlocale(LC_ALL, "rus");
    HWND hwnd          = GetConsoleHwnd();
    HPEN Pen           = CreatePen( PS_SOLID, 1, RGB(255, 0, 0));
    HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
    HDC hDC            = GetDC(hwnd);
    SelectObject(hDC, Pen);
    SelectObject(hDC, hBlackBrush);
    Point3D x, y;

    //for(; t < 1000000000; t += 0.01)
    Point3D a, b, c, d;
        a.ToPoint3D(300, 100, 0);
        b.ToPoint3D(100, -200, 0);
        c.ToPoint3D(-100, -200, 0);
        d.ToPoint3D(-200, 0, 0);

/*while(true)
    {
        osi(hDC, t);

        HPEN Pen = CreatePen( PS_SOLID, 2, RGB(0, 255, 0));
        SelectObject(hDC, Pen);
        Line3D(a, b, hDC, Pen, t);
        Line3D(b, c, hDC, Pen, t);
        Line3D(c, d, hDC, Pen, t);
        Line3D(d, a, hDC, Pen, t);

        Line3D(a, c, hDC, Pen, t);
        Line3D(b, d, hDC, Pen, t);

        Pen = CreatePen( PS_SOLID, 1, RGB(255, 0, 0));
        SelectObject(hDC, Pen);

        Line3D((a + b) * 0.5, (b + c) * 0.5, hDC, Pen, t);
        Line3D((b + c) * 0.5, (c + d) * 0.5, hDC, Pen, t);
        Line3D((c + d) * 0.5, (d + a) * 0.5, hDC, Pen, t);
        Line3D((d + a) * 0.5, (a + b) * 0.5, hDC, Pen, t);

        Line3D((a + b) * 0.5, (c + d) * 0.5, hDC, Pen, t);
        Line3D((a + d) * 0.5, (b + c) * 0.5, hDC, Pen, t);

        Pen = CreatePen( PS_SOLID, 2, RGB(0, 120, 255));
        SelectObject(hDC, Pen);
        Line3D((a + c) * 0.5, (b + d) * 0.5, hDC, Pen, t);

        Pen = CreatePen( PS_SOLID, 3, RGB(255, 0, 0));
        SelectObject(hDC, Pen);
        char ch = getch();
        if(ch == 'a') t -= 0.1;
        if(ch == 'd') t += 0.1;
        if(ch == '=')
        {
            a.x *= 1.1; a.y *= 1.1; a.z *= 1.1;
            b.x *= 1.1; b.y *= 1.1; b.z *= 1.1;
            c.x *= 1.1; c.y *= 1.1; c.z *= 1.1;
            d.x *= 1.1; d.y *= 1.1; d.z *= 1.1;
        }
        if(ch == '-')
        {
            a.x *= 0.9; a.y *= 0.9; a.z *= 0.9;
            b.x *= 0.9; b.y *= 0.9; b.z *= 0.9;
            c.x *= 0.9; c.y *= 0.9; c.z *= 0.9;
            d.x *= 0.9; d.y *= 0.9; d.z *= 0.9;
        }
        if(ch == 'e') break;
        Rectangle(hDC, 10, 10, 600, 600);
    }
*/
    //for(; t < 1000000000; t += 0.1)
    while(true)
    {
        SelectObject(hDC, Pen);
        Rectangle(hDC, 10, 10, 600, 600);
        osi(hDC, t);
        draw(hDC, t, *g, 20, 200 , RGB(0,   255,   0));
        char ch = getch();
        if((ch == 'a') || (ch == 'ф')) t -= 0.1;
        if((ch == 'd') || (ch == 'в')) t += 0.1;
        if(ch == '=')                  ZOOM *= 1.1;
        if(ch == '-')                  ZOOM *= 0.9;
        if((ch == 'e') || (ch == 'у')) break;


        //InvalidateRect(hwnd, NULL, TRUE);
    }




    return 0;
}
