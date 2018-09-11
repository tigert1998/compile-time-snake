#pragma once

#include "pair.hpp"
#include "int.hpp"
#include "if.hpp"

enum class Direction {
    kRightward, kUpward, kLeftward, kDownward
};

template <int X, int Y>
class MakeCoord {
public:
    using Result = Pair<Int<X>, Int<Y>>;
};

template <Direction D, typename Coord>
class MoveCoord {
public:
    using Result =
        typename If<(D == Direction::kRightward),
            typename MakeCoord<Coord::First::value, Coord::Second::value + 1>::Result,
            typename If<(D == Direction::kUpward),
                typename MakeCoord<Coord::First::value - 1, Coord::Second::value>::Result,
                typename If<D == Direction::kLeftward,
                    typename MakeCoord<Coord::First::value, Coord::Second::value - 1>::Result,
                    typename MakeCoord<Coord::First::value + 1, Coord::Second::value>::Result
                >::Result
            >::Result
        >::Result;
};
