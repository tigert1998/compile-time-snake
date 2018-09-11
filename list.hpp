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

template <int n, typename New, typename List>
class ChangeAtIndex {
private:
    using Temp = typename ChangeAtIndex<n - 1, New, typename List::Right>::Result;
public:
    using Result = Cons<typename List::Left, Temp>;
};

template <typename New, typename List>
class ChangeAtIndex<0, New, List> {
public:
    using Result = Cons<New, typename List::Right>;
};

template <typename New, typename List>
class Append {
private:
    using Temp = typename Append<New, typename List::Right>::Result;
public:
    using Result = Cons<typename List::Left, Temp>;
};

template <typename New>
class Append<New, NullList> {
public:
    using Result = Cons<New, NullList>;
};

template <typename List>
class Reverse {
private:
    using Temp = typename Reverse<typename List::Right>::Result;
public:
    using Result = typename Append<typename List::Left, Temp>::Result;
};

template <>
class Reverse<NullList> {
public:
    using Result = NullList;
};

template <typename List>
class Init {
private:
    using Temp = typename Reverse<List>::Result::Right;
public:
    using Result = typename Reverse<Temp>::Result;
};

