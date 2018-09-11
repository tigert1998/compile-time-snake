#include <iostream>

#include "map.hpp"
#include "int.hpp"
#include "snake.hpp"

using std::cout;
using std::endl;

int main() {
    using Snake = MakeList<MakeCoord<1, 1>::Result, MakeCoord<0, 1>::Result, MakeCoord<0, 2>::Result, MakeCoord<1, 2>::Result>::Result;
    cout << IsSelfHit<Direction::kUpward, Snake>::result << endl;
    return 0;
}
