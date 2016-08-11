#include <iostream>
#include <vector>
#include <iterator>

/*
Дерево Фенвика - это структура данных на массиве, позволяющая выполнять следующие операции:
1) Вычислять сумму элементов на некотором отрезке за O(log N)
2) Позволяет изменять значение произвольного элемента за O(log N)
3) Возвращает значение произвольного элемента за O(log N)
*/

template<typename T>
class FenwickTree
{
private:
    std::vector< T > data;
    int size;
public:
    FenwickTree(int size) : size(size)
    {
        data.assign(size, (T)(0));
    }
    FenwickTree(std::vector< T > array) : size(array.size())
    {
        data.assign(size, (T)(0));
        for(int i = 0; i < size; i++)
            inc(i, array[i]);
    }
    T sum(int right)
    {
        T result = (T)0;
        for(; right >= 0; right = (right & (right + 1)) - 1)
            result += data[right];
        return result;
    }
    void inc(int index, T delta)
    {
        for(; index < size; index = (index | (index + 1)))
            data[index] += delta;
    }
    T sum(int left, int right)
    {
        return sum(right) - sum(left - 1);
    }
};

template< typename T >
class PrefixTree
{
private:
    FenwickTree< T > prefix_sums;
    int size;
public:
    PrefixTree(int size) : size(size), prefix_sums(FenwickTree< T >(size)) {}
    void add(int begin_add, int end_add, T value)
    {
        prefix_sums.inc(begin_add, value);
        if (end_add < size - 1)
            prefix_sums.inc(end_add + 1, -value);
    }
    T operator [] (int index)
    {
        return prefix_sums.sum(index);
    }
};

using namespace std;
int main(void)
{
    vector<int> V;
    for(size_t i = 0; i < 10; i++)
        V.push_back(i);
    FenwickTree<int> T(V);
    cout << "Point" << endl;
    for(size_t i = 0; i < 10; i++)
        cout << T.sum(i, i) << " ";
    cout << endl;
    return 0;
}
