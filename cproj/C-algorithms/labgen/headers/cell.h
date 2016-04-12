#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class Cell
{
public:
    bool top_wall, bottom_wall, left_wall, right_wall;
    bool is_part_of_path;
    bool is_way_up, is_way_down, is_way_left, is_way_right;
    std::pair<size_t, size_t> position;
    Cell() :
        top_wall(true), bottom_wall(true), left_wall(true), right_wall(true),
        is_part_of_path(false),
        is_way_up(false), is_way_down(false), is_way_left(false), is_way_right(false),
        position(std::make_pair(-1, -1))
        { }
    Cell(size_t x, size_t y) :
        top_wall(true), bottom_wall(true), left_wall(true), right_wall(true),
        is_part_of_path(false),
        is_way_up(false), is_way_down(false), is_way_left(false), is_way_right(false),
        position(std::make_pair(x, y))
        { }
    friend bool operator < (const Cell & __1, const Cell & __2)
    {
        return (__1.position < __2.position);
    }
};


#endif // CELL_H_INCLUDED
