#include <locale.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include <stack>
using namespace std;
int main(void)
{
    int n; cin >> n;
    for(size_t i = 0; i < n; i++)
    {
        int cur;
        cin >> cur;
        if(cur == 2) cout << "Alice" << endl;
        else if(cur == 3) cout << "Bob" << endl;
        else
        {
            if(cur % 4 < 2) cout << "Alice" << endl;
            else cout << "Bob" << endl;
        }
    }
    return 0;
}