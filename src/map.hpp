#pragma once

#include <iostream>

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

template <typename Coord, typename New, typename Map>
class ChangeAtCoord {
private:
    static constexpr int x = Coord::First::value;
    static constexpr int y = Coord::Second::value;
public:
    using Result = typename ChangeAtXY<x, y, New, Map>::Result;
};

template <typename IntList>
class StringifyIntList {
    friend std::ostream &operator<<(std::ostream &os, const StringifyIntList<IntList> &) {
        os << IntList::Left::value << " ";
        os << StringifyIntList<typename IntList::Right>();
        return os;
    }
};

template <>
class StringifyIntList<NullList> {
    friend std::ostream &operator<<(std::ostream &os, const StringifyIntList<NullList> &) {
        return os;
    }
};

template <typename Map>
class StringifyMap {
    friend std::ostream &operator<<(std::ostream &os, const StringifyMap<Map> &) {
        os << StringifyIntList<typename Map::Left>() << std::endl;
        os << StringifyMap<typename Map::Right>();
        return os;
    }
};

template <>
class StringifyMap<NullList> {
    friend std::ostream &operator<<(std::ostream &os, const StringifyMap<NullList> &) {
        return os;
    }
};
