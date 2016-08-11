#include <iostream>
#include <fstream>
#include "headers/labirint.h"
using namespace std;

int main()
{
    fstream out;
    out.open("text.txt", ios::out);
    Labirint A(20, 20);
    cout << A;
    out.close();
    return 0;
}
