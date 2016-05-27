#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

template<typename T>
void Print(T Container)
{
    copy(Container.begin(), Container.end(), ostream_iterator< int >(cout, " "));
    cout << endl;
}

int main ()
{
    int SS = 2000;
    string a, b;
    cin >> a >> b;
    vector<int> Fi(SS, 0), Se(SS, 0);
    for(int i = a.size() - 1; i >= 0; i--)
    {
        switch(a[i])
        {
        case '0':
            Fi[a.size() - i - 1] = 0;
            break;
        case '1':
            Fi[a.size() - i - 1] = 1;
            break;
        case '$':
            Fi[a.size() - i - 1] = -1;
            break;
        }
    }
    for(int i = b.size() - 1; i >= 0; i--)
    {
        switch(b[i])
        {
        case '0':
            Se[b.size() - i - 1] = 0;
            break;
        case '1':
            Se[b.size() - i - 1] = 1;
            break;
        case '$':
            Se[b.size() - i - 1] = -1;
            break;
        }
    }
    vector<int> Re(SS, 0);
    for(int i = 0; i < SS; i++)
        Re[i] = Fi[i] + Se[i];
    for(int i = 0; i < SS - 1; i++)
    {
        if(Re[i] == -3)
        {
            Re[i] = 0;
            Re[i + 1] -= 1;
        }
        else
            if(Re[i] == -2)
            {
                Re[i] = 1;
                Re[i + 1] -= 1;
            }
            else
                if(Re[i] == 2)
                {
                    Re[i] = -1;
                    Re[i + 1] += 1;
                }
                else
                    if(Re[i] == 3)
                    {
                        Re[i] = 0;
                        Re[i + 1] += 1;
                    }
    }
    int i = SS - 1;
    while(Re[i] == 0)
    {
        i--;
        if(i < 0)
        {
            cout << 0 << endl;
            return 0;
        }
    }
    while(i >= 0)
    {
        if(Re[i] == 1)
            cout << 1 ;
        else
            if(Re[i] == 0)
                cout << 0;
            else
                if(Re[i] == -1)
                    cout << '$';
                else 
                    cout << "^" << Re[i] << "^";
        i--;
    }
    cout << endl;
    return 0;
}