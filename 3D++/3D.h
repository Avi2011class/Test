double ZOOM = 1;
struct Point2D
{
    double x = 0, y = 0;
    void out()
    {
        std::cout << x << " " << y << std::endl;
    }
};
struct Point3D
{
    double x = 0, y = 0, z = 0;
    inline void ToPoint3D(double xx, double yy, double zz)
    {
        x = xx; y = yy; z = zz;
    }
    void out()
    {
        std::cout << x << " " << y << " " << z << std::endl;
    }
    inline Point3D operator +(Point3D pt)
    {
        Point3D tmp;
        tmp.ToPoint3D(x + pt.x, y + pt.y, z + pt.z);
        return tmp;
    }
    inline Point3D operator -(Point3D pt)
    {
        Point3D tmp;
        tmp.ToPoint3D(x - pt.x, y - pt.y, z - pt.z);
        return tmp;
    }
    inline Point3D operator *(double k)
    {
        Point3D tmp;
        tmp.ToPoint3D(x * k, y * k, z * k);
        return tmp;
    }

};

inline Point2D To2D(Point3D p, double phi)
{
    Point3D p1;
    p1.x = p.x * cos(phi) - p.y * sin(phi);
    p1.y = p.x * sin(phi) + p.y * cos(phi);
    p1.z = p.z;


   /* p2.x = p1.x * cos(2*phi) - p1.z * sin(2*phi);
    p2.z = p1.x * sin(2*phi) + p1.z * cos(2*phi);
    p2.y = p1.y;
*/
    Point2D tmp;
    tmp.x = (300 + ZOOM * p1.y - ZOOM * 0.3 * p1.x);
    tmp.y = (300 - ZOOM * p1.z + ZOOM * 0.4 * p1.x);
    return tmp;
}

inline void Line3D(Point3D p1, Point3D p2, HDC hDC, HPEN pen, double phi)
{
    SelectObject( hDC, pen );
    Point2D r1 = To2D(p1, phi), r2 = To2D(p2, phi);
    MoveToEx( hDC, r1.x, r1.y, NULL );
    LineTo( hDC, r2.x, r2.y);
}
inline void MoveTo3D(HDC hDC, Point3D P, double phi)
{
    Point2D tmp = To2D(P, phi);
    MoveToEx( hDC, (int)(tmp.x), (int)(tmp.y), NULL);
}
inline void LineTo3D(HDC hDC, Point3D P, double phi)
{
    Point2D tmp = To2D(P, phi);
    LineTo( hDC, (int)(tmp.x), (int)(tmp.y));
}
inline void osi(HDC hDC, double phi)
{
    HPEN Pen = CreatePen( PS_SOLID, 2, RGB(255, 255, 255));
    Point3D x, y;
    x.ToPoint3D(0, 0, -250);
    y.ToPoint3D(0, 0, 250);
    Line3D(x, y, hDC, Pen, phi);
    x.ToPoint3D(0, 250, 0);
    y.ToPoint3D(0, -250, 0);
    Line3D(x, y, hDC, Pen, phi);
    x.ToPoint3D(250, 0, 0);
    y.ToPoint3D(-250, 0, 0);
    Line3D(x, y, hDC, Pen, phi);
}

inline void draw(HDC hDC, double phi, double (*f)(double x, double y), int N, int T, COLORREF color)
{
    HPEN Pen = CreatePen(PS_SOLID, 1, color);
    SelectObject(hDC, Pen);
    Point3D tmp;

    HDC hMemDC = CreateCompatibleDC(hDC);

    int i, j;
    for(int j1 = (int)(- T / N); j1 <= (T / N); j1++)
    {
        j = j1 * N;
        tmp.ToPoint3D(j, -T, (int)(f(j, -T)));
        MoveTo3D(hDC, tmp, phi);
        for(int i1 = (int)(-T / N); i1 <= (T / N); i1++)
        {
            i = i1 * N;
            tmp.ToPoint3D(j, i, (int)(f(j, i)));
            LineTo3D(hDC, tmp, phi);
        }
    }
    for(int i1 = (int)(-T / N); i1 <= (T / N); i1++)
    {
        i = i1 * N;
        tmp.ToPoint3D(-T, i, (int)(f(-T, i)));
        MoveTo3D(hDC, tmp, phi);
        for(int j1 = (int)(-T / N); j1 <= (T / N); j1++)
        {
            j = j1 * N;
            tmp.ToPoint3D(j, i, (int)(f(j, i)));
            LineTo3D(hDC, tmp, phi);
        }
    }

    BitBlt(hDC, 0, 0, 800, 800, hMemDC, 0, 0, SRCCOPY);
    DeleteDC(hMemDC);
}
