#include <iostream>
#include <vector>

#include <boost/format.hpp>

using boost::format;
using std::vector;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::pair;

const string program_template =
"#include <iostream>\n"
"#include \"map.hpp\"\n"
"#include \"int.hpp\"\n"
"#include \"snake.hpp\"\n"
"using std::cout;\n"
"using std::endl;\n"
"int main() {\n"
"    constexpr Direction direction = static_cast<Direction>(%d);\n"
"    using Map = %s;\n"
"    using Snake = %s;\n"
"    bool is_dead = IsDead<direction, Snake, Map>::result;\n"
"    cout << is_dead << endl;\n"
"    if (is_dead) return 0;\n"
"    cout << static_cast<int>(direction) << endl;\n"
"    using RunResult = Run<Direction::kLeftward, Snake, Map>::Result;\n"
"    using NewSnake = RunResult::First;\n"
"    using NewMap = RunResult::Second;\n"
"    cout << Length<NewSnake>::Result::value << endl;\n"
"    cout << StringifySnake<NewSnake>();\n"
"    int height = Length<NewMap>::Result::value;\n"
"    int width = Length<NewMap::Left>::Result::value;\n"
"    cout << height << \" \" << width << endl;\n"
"    cout << StringifyMap<NewMap>();\n"
"    return 0;\n"
"}\n";

int width, height, direction, len;
vector<vector<int>> map;
vector<pair<int, int>> snake;

string CalcMapStr(const vector<vector<int>> &map) {
    static const auto row_string = [] (const vector<int> &row) -> string {
        string ans = "MakeList<";
        ans += (format("Int<%d>") % row[0]).str();
        for (int i = 1; i < row.size(); i++)
            ans += (format(", Int<%d>") % row[i]).str();
        ans += ">::Result";
        return ans;
    };
    string ans = "MakeList<" + row_string(map[0]);
    for (int i = 1; i < map.size(); i++)
        ans += ", " + row_string(map[i]);
    ans += ">::Result";
    return ans;
}

string CalcSnakeStr(const vector<pair<int, int>> &snake) {
    static const auto pair_string = [] (pair<int, int> p) -> string {
        return (format("MakeCoord<%d, %d>::Result") % p.first % p.second).str();
    };
    string ans = "MakeList<" + pair_string(snake[0]);
    for (int i = 1; i < snake.size(); i++)
        ans += ", " + pair_string(snake[i]);
    ans += ">::Result";
    return ans;
}

int main() {
    cin >> direction >> len;
    snake.resize(len);
    for (int i = 0; i < len; i++) cin >> snake[i].first >> snake[i].second;
    cin >> height >> width;
    map.resize(height);
    for (int i = 0; i < height; i++) {
        map[i].resize(width);
        for (int j = 0; j < width; j++) cin >> map[i][j];
    }
    string program = (format(program_template) % direction % CalcMapStr(map).c_str() % CalcSnakeStr(snake).c_str()).str();
    cout << program;
    return 0;
}
