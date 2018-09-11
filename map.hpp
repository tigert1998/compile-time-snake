#pragma once

#include "list.hpp"

template <int x, int y, typename Map>
class ValueAtXY {
private:
    using Row = typename ValueAtIndex<x, Map>::Result;
public:
    using Result = typename ValueAtIndex<y, Row>::Result;
};

template <typename Coord, typename Map>
class ValueAtCoord {
private:
    static constexpr int x = Coord::First::value;
    static constexpr int y = Coord::Second::value;
public:
    using Result = typename ValueAtXY<x, y, Map>::Result;
};

