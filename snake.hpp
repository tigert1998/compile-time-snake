#pragma once

#include "list.hpp"
#include "coord.hpp"

template <typename Coord, typename CoordList>
class CoordExists {
private:
    static constexpr bool current_result = CoordEqual<typename CoordList::Left, Coord>::result;
public:
    static constexpr bool result = current_result || CoordExists<Coord, typename CoordList::Right>::result;
};

template <typename Coord>
class CoordExists<Coord, NullList> {
public:
    static constexpr bool result = false;
};

template <Direction d, typename Snake, typename Map>
class IsDead {
private:
    using HeadCoord = typename Snake::Left;
    using NewHeadCoord = typename MoveCoord<d, HeadCoord>::Result;
    static constexpr bool hit_self = CoordExists<NewHeadCoord, Snake>::result;
    static constexpr bool out_of_wall = !CoordInMap<NewHeadCoord, Map>::result;
public:
    static constexpr bool result = hit_self || out_of_wall;
};

