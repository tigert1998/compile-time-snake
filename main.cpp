#include <iostream>

#include "map.hpp"
#include "int.hpp"

using std::cout;
using std::endl;

int main() {
    using Map = MakeList<MakeList<Int<1>, Int<2>>::Result, MakeList<Int<3>, Int<4>>::Result>::Result;
    using Value = ValueAtCoord<1, 1, Map>::Result;
    cout << typeid(Value).name() << endl;
    return 0;
}
