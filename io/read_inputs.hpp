#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

inline vector<string> read_inputs(const string& filename) {
    // Read input file
    std::ifstream infile(filename);
    string line;
    vector<string> output;

    while (std::getline(infile, line)) {
        output.push_back(line);
    }
    return output;
}
