#include <iostream>

using namespace std;

int main()
{
    char a, b, c;
    cin >> a >> b >> c;
    a -= 48;
    b -= 48;
    c -= 48;
    if(a & 4)
        cout << 'r';
    else
        cout << '-';
    if(a & 2)
        cout << 'w';
    else
        cout << '-';
    if(a & 1)
        cout << 'x';
    else
        cout << '-';

    if(b & 4)
        cout << 'r';
    else
        cout << '-';
    if(b & 2)
        cout << 'w';
    else
        cout << '-';
    if(b & 1)
        cout << 'x';
    else
        cout << '-';

    if(c & 4)
        cout << 'r';
    else
        cout << '-';
    if(c & 2)
        cout << 'w';
    else
        cout << '-';
    if(c & 1)
        cout << 'x';
    else
        cout << '-';
    return 0;

}
