#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>

using namespace std;
template<typename T>
void PrintContainer(T Container)
// Шаблон отладочной функции вывода STL-контейнера на печать
{
    copy(Container.begin(), Container.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
long long int GCD(long long int a, long long int b)
{
    if(a * b == 0)
        return abs(a + b);
    a = abs(a);
    b = abs(b);
    long long int buffer;
    while(b != 0)
    {
        buffer = a % b;
        a = b;
        b = buffer;
    }
    return a;
}
inline long long int NOK(long long int a, long long int b)
{
    return a / GCD(a, b) * b;
}
inline void StringSplit(string Str, string & StrIntPart, string & StrFracPart, string & StrInfPart)
{
    if(Str.find(".") == string::npos)
    {
        StrIntPart = Str;
        StrFracPart = "";
        StrInfPart = "0";
    }
    else
    {
        StrIntPart = Str.substr(0, Str.find("."));
        Str = Str.substr(Str.find(".") + 1);
        if(Str.find("(") == string::npos)
        {
            StrFracPart = Str;
            StrInfPart = "0";
        }
        else
        {
            StrFracPart = Str.substr(0, Str.find("("));
            Str = Str.substr(Str.find("(") + 1);
            StrInfPart = Str.substr(0, Str.length() - 1);
        }
    }
}
string ShortestPeriod(string Str)
// Функция поиска наименьшего периода (123123) -> (123), (111111) -> (1)
{
    set<int> LengthDivisors;
    int Length = Str.length();
    for(int i = 1; i < sqrt(Length) + 2; i++)
        if(Length % i == 0)
        {
            LengthDivisors.insert(i);
            LengthDivisors.insert((int)(Length / i));
        }
    for(set<int>::iterator it = LengthDivisors.begin(); it != LengthDivisors.end(); it++)
    {
        bool CorrectPeriod = true;
        for(size_t i = 0; i < *it && CorrectPeriod; i++)
            for(size_t j = i; j < Length && CorrectPeriod; j += *it)
                if(Str[j] != Str[i])
                    CorrectPeriod = false;
        if(CorrectPeriod)
            return Str.substr(0, *it);
    }
    return Str;
}
int main(int argc, char** argv)
{
    string First, Second;
    cin >> First >> Second;
    string FirstIntPart, SecondIntPart;
    string FirstFracPart, SecondFracPart;
    string FirstInfPart, SecondInfPart;
    StringSplit(First, FirstIntPart, FirstFracPart, FirstInfPart);
    StringSplit(Second, SecondIntPart, SecondFracPart, SecondInfPart);
    // Сделаем так, чтобы FirstFracPart <= SecondFracPart
    if(FirstFracPart.length() > SecondFracPart.length())
    {
        swap(FirstIntPart, SecondIntPart);
        swap(FirstFracPart, SecondFracPart);
        swap(FirstInfPart, SecondInfPart);
    }
    // Выравняем дробные части
    while(FirstFracPart.length() < SecondFracPart.length())
    {
        FirstFracPart += FirstInfPart[0];
        if(FirstInfPart.length() > 1)
            FirstInfPart = FirstInfPart.substr(1) + FirstInfPart[0];
    }

    // Приведем длины периодических частей
    int LengthInfPart = NOK(FirstInfPart.length(), SecondInfPart.length());

    int LastFirstInfLength = FirstInfPart.length();
    int LastSecondInfLength = SecondInfPart.length();
    FirstInfPart.resize(LengthInfPart, '0');
    SecondInfPart.resize(LengthInfPart, '0');

    for(size_t i = 0; i < LengthInfPart; i++)
    {
        FirstInfPart[i] = FirstInfPart[i % LastFirstInfLength];
        SecondInfPart[i] = SecondInfPart[i % LastSecondInfLength];
    }

    // Приведем длины целых частей
    int LengthIntPart = max(FirstIntPart.length(), SecondIntPart.length()) + 2;
    while(FirstIntPart.length() < LengthIntPart)
        FirstIntPart = "0" + FirstIntPart;
    while(SecondIntPart.length() < LengthIntPart)
        SecondIntPart = "0" + SecondIntPart;


    // Сложим периодические части и запишем в First
    int buffer = 0;
    for(int i = LengthInfPart - 1; i >= 0; i--)
    {
        FirstInfPart[i] += SecondInfPart[i] - '0' + buffer;
        if(FirstInfPart[i] > '9')
        {
            buffer = 1;
            FirstInfPart[i] -= 10;
        }
        else
        {
            buffer = 0;
        }
    }
    if(buffer == 1)
        FirstInfPart[LengthInfPart - 1] += 1;
    if(FirstInfPart[LengthInfPart - 1] == ':')
    {
        FirstInfPart[LengthInfPart - 1] -= 10;
        FirstInfPart[LengthInfPart - 2] += 1;
    }

    // Сложим дробные части
    for(int i = FirstFracPart.length() - 1; i >= 0; i--)
    {
        FirstFracPart[i] += SecondFracPart[i] - '0' + buffer;
        if(FirstFracPart[i] > '9')
        {
            buffer = 1;
            FirstFracPart[i] -= 10;
        }
        else
        {
            buffer = 0;
        }
    }

    // Сложим целые части
    for(int i = LengthIntPart - 1; i >= 0; i--)
    {
        FirstIntPart[i] += SecondIntPart[i] - '0' + buffer;
        if(FirstIntPart[i] > '9')
        {
            buffer = 1;
            FirstIntPart[i] -= 10;
        }
        else
        {
            buffer = 0;
        }
    }
    // Сокращаем период дроби и избавляемся от возможного периода (9)
    FirstInfPart = ShortestPeriod(FirstInfPart);
    if(FirstInfPart == "9")
    {
        FirstInfPart = "0";
        buffer = 1;
        for(int i = FirstFracPart.length() - 1; i >= 0; i--)
        {
            FirstFracPart[i] += buffer;
            if(FirstFracPart[i] > '9')
            {
                FirstFracPart[i] -= 10;
                buffer = 1;
            }
            else
            {
                buffer = 0;
            }
        }
        for(int i = LengthIntPart - 1; i >= 0; i--)
        {
            FirstIntPart[i] += buffer;
            if(FirstIntPart[i] > '9')
            {
                FirstIntPart[i] -= 10;
                buffer = 1;
            }
            else
            {
                buffer = 0;
            }
        }
    }
    // Пытаемся максимально поместить дробную часть внутрь периода
    {
        while(true)
        {
            if(FirstFracPart.length() == 0)
                break;
            else
                if(FirstInfPart.length() == 0)
                    break;
                else
                    if(FirstFracPart[FirstFracPart.length() - 1] == FirstInfPart[FirstInfPart.length() - 1])
                    {
                        if(FirstInfPart.length() > 1)
                            FirstInfPart = FirstInfPart[FirstInfPart.length() - 1] + FirstInfPart.substr(0, FirstInfPart.length() - 1);
                        FirstFracPart = FirstFracPart.substr(0, FirstFracPart.length() - 1);
                    }
                    else
                        break;
        }
    }
    // Аккуратно выводим результат
    bool IntNull = true;
    int iter = 0;
    for(iter = 0; iter < LengthIntPart && IntNull; iter++)
        if(FirstIntPart[iter] != '0')
            IntNull = false;

    if(IntNull)
        cout << 0;
    else
        cout << FirstIntPart.substr(iter - 1);

    if(FirstFracPart != "" || FirstInfPart != "0")
    {
        cout << ".";
        if(FirstFracPart != "")
            cout << FirstFracPart;
        if(FirstInfPart != "0")
            cout << "(" << FirstInfPart << ")";
    }
    cout << endl;
    return 0;
}