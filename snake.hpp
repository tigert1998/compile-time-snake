#pragma once

#include "map.hpp"
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
    using Value = typename ValueAtCoord<NewHeadCoord, Map>::Result;
    static constexpr bool hit_self = CoordExists<NewHeadCoord, Snake>::result;
    static constexpr bool out_of_map = !CoordInMap<NewHeadCoord, Map>::result;
    static constexpr bool into_wall = static_cast<TileType>(Value::value) == TileType::kWall;
public:
    static constexpr bool result = hit_self || out_of_map || into_wall;
};

template <Direction d, typename Snake, typename Map>
class Run {
private:
    using HeadCoord = typename Snake::Left;
    using NewHeadCoord = typename MoveCoord<d, HeadCoord>::Result;
    using PlusNewHead = Cons<NewHeadCoord, Snake>;
    using Value = typename ValueAtCoord<NewHeadCoord, Map>::Result;
    static constexpr bool eat = static_cast<TileType>(Value::value) == TileType::kFood;
public:
    using Result = typename If<eat,
        PlusNewHead,
        typename Init<PlusNewHead>::Result
    >::Result;
};
