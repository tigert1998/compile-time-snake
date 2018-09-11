#pragma once

template <bool Predicate, typename Then, typename Else>
class If {};

template <typename Then, typename Else>
class If<true, Then, Else> {
public:
    using Result = Then;
};

template <typename Then, typename Else>
class If<false, Then, Else> {
public:
    using Result = Else;
};

