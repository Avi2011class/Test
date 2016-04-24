#ifndef DSU_H_INCLUDED
#define DSU_H_INCLUDED
#include <vector>

class DSU
{
private:
    size_t size;
    std::vector<size_t> Parent;
    std::vector<size_t> Range;
public:
    DSU(size_t size) :
        size(size),
        Parent(std::vector<size_t>(size)),
        Range(std::vector<size_t>(size))
    {
        for(size_t i = 0; i < size; i++)
        {
            Parent[i] = i;
            Range[i] = 1;
        }
    }
private:
    size_t find_set(size_t V)
    {
        if(Parent[V] == V)
            return V;
        else
        {
            Parent[V] = find_set(Parent[V]);
            return Parent[V];
        }
    }
public:
    void union_sets(size_t X, size_t Y)
    {
        X = find_set(X);
        Y = find_set(Y);
        if(X != Y)
        {
            if(Range[X] < Range[Y])
                std::swap(X, Y);
            Parent[Y] = X;
            Range[X] += Range[Y];
        }
    }
    bool is_sets_equal(size_t X, size_t Y)
    {
        return (find_set(X) == find_set(Y));
    }
};

#endif // DSU_H_INCLUDED
