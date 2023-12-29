#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "read_inputs.hpp"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

void remove_prefix(string& line) { line.erase(0, line.find(":") + 1); }

int calculate_points(string& line) {
    remove_prefix(line);

    stringstream line_stream(line);
    string scratched_part;
    // Parse the input line until the '|' character to get the scratched numbers
    std::getline(line_stream, scratched_part, '|');

    // Create a stringstream to parse the input string
    stringstream scratched_stream(scratched_part);

    // Create a set of all scratched numbers
    std::unordered_set<int> scratched_set;
    int n;
    while (scratched_stream >> n) {
        scratched_set.insert(n);
    }

    // The remainder of the line_stream are the winning numbers
    int matches = 0;
    while (line_stream >> n) {
        // Count how many times the winning number n appears in the scratched number set
        matches += scratched_set.count(n);
    }

    if (matches == 0) return 0;

    return std::pow(2, matches - 1);
}

int main() {
    int result = 0;

    auto lines = read_inputs("data/input.txt");
    std::ifstream infile("data/input.txt");
    string line;
    while (std::getline(infile, line)) {
        result += calculate_points(line);
    }

    cout << "Result: " << result << endl;
}
