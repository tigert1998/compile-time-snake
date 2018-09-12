#include <iostream>
#include "map.hpp"
#include "int.hpp"
#include "snake.hpp"
using std::cout;
using std::endl;
int main() {
    constexpr Direction direction = static_cast<Direction>(0);
    using Map = MakeList<MakeList<Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>>::Result, MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, MakeList<Int<2>, Int<0>, Int<0>, Int<1>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, MakeList<Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>>::Result>::Result;
    using Snake = MakeList<MakeCoord<2, 7>::Result, MakeCoord<2, 6>::Result, MakeCoord<2, 5>::Result, MakeCoord<1, 5>::Result, MakeCoord<1, 4>::Result, MakeCoord<1, 3>::Result, MakeCoord<1, 2>::Result, MakeCoord<1, 1>::Result, MakeCoord<2, 1>::Result, MakeCoord<3, 1>::Result, MakeCoord<4, 1>::Result, MakeCoord<4, 2>::Result, MakeCoord<3, 2>::Result, MakeCoord<2, 2>::Result, MakeCoord<2, 3>::Result>::Result;
    bool is_dead = IsDead<direction, Snake, Map>::result;
    cout << is_dead << endl;
    if (is_dead) return 0;
    cout << static_cast<int>(direction) << endl;
    using RunResult = Run<direction, Snake, Map>::Result;
    using NewSnake = RunResult::First;
    using NewMap = RunResult::Second;
    cout << Length<NewSnake>::Result::value << endl;
    cout << StringifySnake<NewSnake>();
    int height = Length<NewMap>::Result::value;
    int width = Length<NewMap::Left>::Result::value;
    cout << height << " " << width << endl;
    cout << StringifyMap<NewMap>();
    return 0;
}
