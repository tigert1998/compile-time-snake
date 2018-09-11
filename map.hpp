#pragma once

#include "list.hpp"

template <int X, int Y, typename Map>
class ValueAtCoord {
private:
    using Row = typename ValueAtIndex<X, Map>::Result;
public:
    using Result = typename ValueAtIndex<Y, Row>::Result;
};

