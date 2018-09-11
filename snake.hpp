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

template <Direction d, typename Snake>
class IsSelfHit {
private:
    using NewHeadCoord = typename MoveCoord<d, typename Snake::Left>::Result;
public:
    static constexpr bool result = CoordExists<NewHeadCoord, Snake>::result;
};

