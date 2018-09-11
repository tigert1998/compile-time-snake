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

template <int x, int y, typename New, typename Map>
class ChangeAtXY {
private:
    using Row = typename ValueAtIndex<x, Map>::Result;
    using NewRow = typename ChangeAtIndex<y, New, Row>::Result;
public:
    using Result = typename ChangeAtIndex<x, NewRow, Map>::Result;
};
