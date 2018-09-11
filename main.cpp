#include <iostream>

#include "map.hpp"
#include "int.hpp"
#include "coord.hpp"

using std::cout;
using std::endl;

int main() {
    using Coord = MakeCoord<1, 0>::Result;
    using NewCoord = MoveCoord<Direction::kUpward, Coord>::Result;
    using Map = MakeList<MakeList<Int<1>, Int<2>>::Result, MakeList<Int<3>, Int<4>>::Result>::Result;
    using Value = ValueAtCoord<NewCoord, Map>::Result;
    using Len = Length<Map>::Result;
    cout << typeid(Value).name() << endl;
    cout << typeid(Len).name() << endl;
    return 0;
}
