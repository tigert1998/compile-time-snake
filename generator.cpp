#include <iostream>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/format.hpp>

using boost::format;
using std::vector;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::string;

int width, height;
vector<vector<int>> map;

void Init(int argc, char **argv) {
    namespace po = boost::program_options;
    po::options_description desc;
    desc.add_options()
        ("help", "produce help message")
        ("width", po::value<int>(), "set width for the chessboard")
        ("height", po::value<int>(), "set height for the chessboard");
    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (vm.count("help")) {
            cerr << desc << endl;
            exit(1);
        }
        if (!vm.count("width") || !vm.count("height")) {
            cerr << "Not sufficient arguments" << endl;
            exit(1);
        }
        width = vm["width"].as<int>();
        height = vm["height"].as<int>();
        if (width <= 0 || height <= 0) {
            cerr << "Invalid arguments" << endl;
            exit(1);
        }
    } catch (...) {
        cerr << desc << endl;
        exit(1);
    }
}

string CalculateTypeString(const vector<vector<int>> &map) {
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

int main(int argc, char **argv) {
    Init(argc, argv);
    map.resize(height);
    for (int i = 0; i < height; i++) {
        map[i].resize(width);
        for (int j = 0; j < width; j++) cin >> map[i][j];
    }
    string ans = CalculateTypeString(map);
    cout << ans << endl;
    return 0;
}
