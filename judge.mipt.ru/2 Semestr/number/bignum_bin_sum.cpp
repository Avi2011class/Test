#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;

    string::iterator it;

    it = a.begin();
    while (*it == '0' && (it + 1 != a.end()))
        it++;
    a.erase (a.begin(), it);

    it = b.begin();
    while (*it == '0' && (it + 1 != b.end()))
        it++;

    b.erase (b.begin(), it);

    a.insert (0, max (a.size(), b.size()) - a.size() + 1, '0');
    b.insert (0, max (a.size(), b.size()) - b.size(), '0');

    int i = a.size();
    int buf = 0;
    do
    {
        i--;
        a[i] = a[i] - '0' + b[i] + buf;
        switch (a[i])
        {
        case '1':
            buf = 0;
            break;
        case '2':
            a[i] = '0';
            buf = 1;
            break;
        case '3':
            a[i] = '1';
            buf = 1;
            break;
        }
    }
    while (i);
    it = a.begin();
    while (*it == '0' && (it + 1 != a.end()))
        it++;
    a.erase (a.begin(), it);
    cout << a << endl;

    return 0;
}