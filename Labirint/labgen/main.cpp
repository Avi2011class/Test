#include <iostream>
#include <fstream>
#include "headers/labirint.h"
using namespace std;

int main()
{
    fstream out;
    out.open("text.txt", ios::out);
    int a, b;
    cin >> a >> b;
    Labirint A(a, b);
    out << A;
    out.close();
    return 0;
}
