#pragma once

#include "if.hpp"
#include "int.hpp"

class NullList {};

template <typename L, typename R>
class Cons {
public:
    using Left = L;
    using Right = R;
};

template <typename ...Args>
class MakeList {};

template <typename Head, typename ...Tail>
class MakeList<Head, Tail...> {
public:
    using Result = Cons<Head, typename MakeList<Tail...>::Result>;
};

template <typename Head>
class MakeList<Head> {
public:
    using Result = Cons<Head, NullList>;
};

template <>
class MakeList<> {
public:
    using Result = NullList;
};

template <int n, typename List>
class ValueAtIndex {
public:
    using Result = typename ValueAtIndex<n - 1, typename List::Right>::Result;
};

template <typename List>
class ValueAtIndex<0, List> {
public:
    using Result = typename List::Left;
};

template <typename List>
class Length {
public:
    using Result = Int<Length<typename List::Right>::Result::value + 1>;
};

template <>
class Length<NullList> {
public:
    using Result = Int<0>;
};
