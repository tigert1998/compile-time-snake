#pragma once

#include "pair.hpp"
#include "int.hpp"
#include "if.hpp"

enum class Direction {
    kRightward, kUpward, kLeftward, kDownward
};

template <int x, int y>
class MakeCoord {
public:
    using Result = Pair<Int<x>, Int<y>>;
};

template <Direction d, typename Coord>
class MoveCoord {
public:
    using Result =
        typename If<(d == Direction::kRightward),
            typename MakeCoord<Coord::First::value, Coord::Second::value + 1>::Result,
            typename If<(d == Direction::kUpward),
                typename MakeCoord<Coord::First::value - 1, Coord::Second::value>::Result,
                typename If<d == Direction::kLeftward,
                    typename MakeCoord<Coord::First::value, Coord::Second::value - 1>::Result,
                    typename MakeCoord<Coord::First::value + 1, Coord::Second::value>::Result
                >::Result
            >::Result
        >::Result;
};

template <typename A, typename B>
class CoordEqual {
public:
    static constexpr bool result = A::First::value == B::First::value && A::Second::value == B::Second::value;
};

template <typename Coord, typename Map>
class CoordInMap {
private:
    static constexpr int height = Length<Map>::Result::value;
    static constexpr int width = Length<typename Map::Left>::Result::value;
    static constexpr int x = Coord::First::value;
    static constexpr int y = Coord::Second::value;
public:
    static constexpr bool result =
        x >= 0 &&
        y >= 0 &&
        x < height &&
        y < width;
};
