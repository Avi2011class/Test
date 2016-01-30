#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>

#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <tchar.h>

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
double SPEED1, SPEED2, SPEED3, A1, A2, A3, C1, C2, C3, F1, F2, F3;
HWND WINAPI GetConsoleWindow();
double f(double x, double t)
{
    return A1 * sin(3.14159265 * C1 * (x - SPEED1 * t) + F1);
}
double g(double x, double t)
{
    return A2 * sin(3.14159265 * C2 * (x - SPEED2 * t) + F2);
}
double q(double x, double t)
{
    return A3 * sin(3.14159265 * C3 * (x - SPEED3 * t) + F3);
}
double k(double x, double t)
{
    return f(x, t) + g(x, t) + q(x, t);
}
//#define GetConsoleHwnd() FindWindow(NULL, _T("Калькулятор"))
int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "rus");
    system("title Graph");
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    int background = 0; // 0000
    int foreground = 12; // 0001
    SetConsoleTextAttribute(hcon, (background << 4) | foreground);
    cout << "Скорость, амплитуда, начальная фаза и частота первой волны: ";
    cin >> SPEED1 >> A1 >> F1 >> C1;
    background = 0; // 0000
    foreground = 11; // 0001
    SetConsoleTextAttribute(hcon, (background << 4) | foreground);
    cout << "Скорость, амплитуда, начальная фаза и частота второй волны: ";
    cin >> SPEED2 >> A2 >> F2 >> C2;
    background = 0; // 0000
    foreground = 9; // 0001
    SetConsoleTextAttribute(hcon, (background << 4) | foreground);
    cout << "Скорость, амплитуда, начальная фаза и частота третьей волны: ";
    cin >> SPEED3 >> A3 >> F3 >> C3;
    background = 0; // 0000
    foreground = 10; // 0001
    SetConsoleTextAttribute(hcon, (background << 4) | foreground);
    cout << "\nЗеленая волна - результат сложения синей и красной\n" ;
    ////////////////////////////////
    size_t HEIGHT = 500, WIDTH = 900, STEP = 10;
    //////////////////////////////////////
    double EPS = 0.1;
    HDC hDC = GetDC(GetConsoleHwnd());
    //////////////////////////////////////////////////////
    /*for(size_t i = 0; i < HEIGHT; i += STEP)
    {
    	if(i == HEIGHT / 2)
    	{
    		HPEN Pen = CreatePen( PS_SOLID, 2, RGB(0, 255, 0));
    		SelectObject( hDC, Pen );
    	}
    	else if((i - HEIGHT / 2) % (STEP * 5) == 0 || ( HEIGHT / 2 - i) % 50 == 0)
    	{
    		HPEN Pen = CreatePen( PS_SOLID, 1, RGB(0, 200, 0));
    		SelectObject( hDC, Pen );
    	}
    	else
    	{
    		HPEN Pen = CreatePen( PS_SOLID, 1, RGB(0, 100, 0));
    		SelectObject( hDC, Pen );
    	}
    	MoveToEx( hDC, 0, i, NULL );
    	LineTo( hDC, WIDTH, i );
    }
    for(size_t i = 0; i < WIDTH; i += STEP)
    {
    	if(i == WIDTH / 2)
    	{
    		HPEN Pen = CreatePen( PS_SOLID, 2, RGB(0, 255, 0));
    		SelectObject( hDC, Pen );
    	}
    	else if((i - WIDTH / 2) % (STEP * 5) == 0 || ( WIDTH / 2 - i) % 50 == 0)
    	{
    		HPEN Pen = CreatePen( PS_SOLID, 1, RGB(0, 200, 0));
    		SelectObject( hDC, Pen );
    	}
    	else
    	{
    		HPEN Pen = CreatePen( PS_SOLID, 1, RGB(0, 100, 0));
    		SelectObject( hDC, Pen );
    	}
    	MoveToEx( hDC, i, 0, NULL );
    	LineTo( hDC, i, HEIGHT );
    }
    */
    /////////////////////////////////////////////////////////
    /*
    HPEN Pen = CreatePen( PS_SOLID, 2, RGB(255, 0, 0));
    SelectObject( hDC, Pen );
    for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
    {
    	MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - f(i - EPS) * STEP * 5), NULL );
    	LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - f(i) * STEP * 5));
    }
    */
    //////////////////////////////////////////////////////////
    for(double j = 0; j < 100000000000; j = j + EPS)
    {
        HPEN Pen = CreatePen( PS_SOLID, 2, RGB(255, 0, 0));
        SelectObject( hDC, Pen );
        for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
        {
            MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - g(i - EPS, j) * STEP * 5), NULL );
            LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - g(i, j) * STEP * 5));
        }
        Pen = CreatePen( PS_SOLID, 2, RGB(0, 255, 255));
        SelectObject( hDC, Pen );
        for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
        {
            MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - f(i - EPS, j) * STEP * 5), NULL );
            LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - f(i, j) * STEP * 5));
        }
        Pen = CreatePen( PS_SOLID, 2, RGB(0, 0, 255));
        SelectObject( hDC, Pen );
        for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
        {
            MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - q(i - EPS, j) * STEP * 5), NULL );
            LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - q(i, j) * STEP * 5));
        }
        Pen = CreatePen( PS_SOLID, 2, RGB(0, 255, 0));
        SelectObject( hDC, Pen );
        for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
        {
            MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - k(i - EPS, j) * STEP * 5), NULL );
            LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - k(i, j) * STEP * 5));
        }

        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Sleep(10);

        Pen = CreatePen( PS_SOLID, 2, RGB(0, 0, 0));
        SelectObject( hDC, Pen );
        for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
        {
            MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - g(i - EPS, j) * STEP * 5), NULL );
            LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - g(i, j) * STEP * 5));
        }
        for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
        {
            MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - f(i - EPS, j) * STEP * 5), NULL );
            LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - f(i, j) * STEP * 5));
        }
        for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
        {
            MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - q(i - EPS, j) * STEP * 5), NULL );
            LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - q(i, j) * STEP * 5));
        }
        for(double i = -(double)(WIDTH / STEP / 10); i < WIDTH / STEP / 10; i += EPS)
        {
            MoveToEx( hDC, (int)(WIDTH/2 + (i - EPS) * STEP * 5), (int)(HEIGHT / 2 - k(i - EPS, j) * STEP * 5), NULL );
            LineTo( hDC, (int)(WIDTH/2 + (i) * STEP * 5), (int)(HEIGHT / 2 - k(i, j) * STEP * 5));
        }

        //InvalidateRect(GetConsoleWindow(), NULL, TRUE);
    }
    //////////////////////////////////////////////////////////

    system("pause");
}
