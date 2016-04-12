#ifndef LABIRINT_H_INCLUDED
#define LABIRINT_H_INCLUDED

#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <map>

#include "DSU.h"
#include "cell.h"

class Labirint
{
private:
    size_t height;
    size_t width;
    std::vector< std::vector< Cell > > field;
    void remove_wall(std::pair<size_t, size_t> __1, std::pair<size_t, size_t> __2)
    {
        if(__1 > __2)
            std::swap(__1, __2);

        if(__1.first  == __2.first && __1.second + 1 == __2.second)
        {
            field[__1.first][__1.second].right_wall = false;
            field[__2.first][__2.second].left_wall = false;
        }
        else
            if(__1.first + 1 == __2.first && __1.second == __2.second)
            {
                field[__1.first][__1.second].bottom_wall = false;
                field[__2.first][__2.second].top_wall = false;
            }
    }
    void refresh()
    {
        std::vector< std::pair< size_t, std::pair<Cell, Cell> > > edges;
        edges.reserve(width * height - width - height);
        for(size_t i = 0; i < height; i++)
            for(size_t j = 0; j < width - 1; j++)
                edges.push_back(std::make_pair(rand(),
                                std::make_pair( Cell(i, j), Cell(i, j + 1) )));
        for(size_t i = 0; i < height - 1; i++)
            for(size_t j = 0; j < width; j++)
                edges.push_back(std::make_pair(rand(),
                                std::make_pair( Cell(i, j), Cell(i + 1, j) )));

        //for(size_t i = 0; i < edges.size(); i++)
        //    std::swap(edges[i], edges[rand() % edges.size()]);
        
        std::sort(edges.begin(), edges.end());

        DSU D(width * height);
        int count = 0;
        for(std::pair< size_t, std::pair<Cell, Cell> > & E : edges)
        {
            if(!D.is_sets_equal(width * E.second.first.position.first 
                                    + E.second.first.position.second,
                                width * E.second.second.position.first 
                                    + E.second.second.position.second))
            {
                D.union_sets(width * E.second.first.position.first  
                                    + E.second.first.position.second,
                             width * E.second.second.position.first 
                                    + E.second.second.position.second);
                remove_wall(E.second.first.position, E.second.second.position);
                count++;
                if(count == height * width - 1)
                    break;
            }
        }
    }
public:
    Labirint(size_t height, size_t width) :
        height(height), width(width)
    {
        srand(clock());
        field.resize(height);
        for(size_t i = 0; i < height; i++)
            field[i].assign(width, Cell());
        refresh();
    }
    friend std::ostream & operator << (std::ostream & output_stream, Labirint & L)
    {
        output_stream << "┌";
        for(size_t i = 0; i < L.width - 1; i++)
            output_stream << "───┬";
        output_stream << "───┐";
        output_stream << "\n";

        for(size_t i = 0; i < L.height; i++)
        {
            output_stream << "│";
            for(size_t j = 0; j < L.width; j++)
                output_stream << (L.field[i][j].right_wall ? "   │" : "    ");
            output_stream << "\n";
            if(i != L.height - 1)
            {
                output_stream << "├";
                for(size_t j = 0; j < L.width - 1; j++)
                    output_stream << (L.field[i][j].bottom_wall  ? "───┼" : "   ┼");
                output_stream << (L.field[i][L.width - 1].bottom_wall ? "───┤" : "   ┤") ;
                output_stream << "\n";
            }
            else
            {
                output_stream << "└";
                for(size_t i = 0; i < L.width - 1; i++)
                    output_stream << "───┴";
                output_stream << "───┘";
                output_stream << "\n";
            }
        }
        return output_stream;
    }
};


#endif // LABIRINT_H_INCLUDED
