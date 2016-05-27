#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

int main(void)
{
    int x; cin >> x;
    int a1, b1, c1;
    int a2 = 0, b2 = 0, c2 = 0;
    for(int a = 1; a < x; a++)
        for(int b = 0; b < x; b++)
            for(int c = 0; c < x; c++)
            {
                c1 = c * c;
                b1 = 2 * b * c;
                a1 = 2 * a * c + b * b;

                b1 += c1 / x;
                c1 = c1 % x;

                a1 += b1 / x;
                b1 = b1 % x;

                a1 = a1 % x;
                if(a == a1 && b == b1 && c == c1)
                {
                    a2 = a;
                    b2 = b;
                    c2 = c;
                }
            }
    if(a2 != 0)
        cout << a2 * x * x + b2 * x + c2 << endl;
    else
        cout << 0 << endl;
    return 0;
}