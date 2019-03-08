# A snake running in compiling time

It's a compiling time snake as is mentioned in the title. **Nearly all game logics are implemented within `C++`'s compiling time** while the `python` script are used only to render the map, generate food locations and transfer necessary data.

```cpp
// input
using Map = MakeList<
    MakeList<Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>>::Result, 
    MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, 
    MakeList<Int<2>, Int<1>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, 
    MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, 
    MakeList<Int<2>, Int<0>, Int<0>, Int<0>, Int<0>, Int<2>>::Result, 
    MakeList<Int<2>, Int<2>, Int<2>, Int<2>, Int<2>, Int<2>>::Result>::Result;
using Snake = MakeList<
    MakeCoord<2, 2>::Result, 
    MakeCoord<2, 3>::Result, 
    MakeCoord<2, 4>::Result, 
    MakeCoord<3, 4>::Result>::Result;
    
/*
Map ==
    ######
    #....#
    #*@oo#
    #...o#
    #....#
    ######
*/

// output
bool is_dead = IsDead<direction, Snake, Map>::result;
using RunResult = Run<direction, Snake, Map>::Result;
using NewSnake = RunResult::First;
using NewMap = RunResult::Second;

/*
is_dead == false

NewSnake == MakeList<
    MakeCoord<2, 1>::Result,
    MakeCoord<2, 2>::Result, 
    MakeCoord<2, 3>::Result, 
    MakeCoord<2, 4>::Result, 
    MakeCoord<3, 4>::Result>::Result

NewMap ==
    ######
    #....#
    #@ooo#
    #...o#
    #....#
    ######
*/
```

## Prerequisite

- Python3
- A third party python package `click`, installed by `pip`
- `boost.format`
- `-std=c++11`

## Usage

1. Change directory to `build` and run `make init`
2. `make run`

