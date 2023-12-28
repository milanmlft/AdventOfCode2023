#include <array>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "read_inputs.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct SymbolLocation {
    int line;
    int position;

    SymbolLocation(int l, size_t p) {
        line = l;
        position = int(p);
    }
};

vector<SymbolLocation> find_symbol_positions(const vector<string>& lines,
                                             const string& regex = "[^\\d.]") {
    vector<SymbolLocation> positions;

    // Regex set up
    std::smatch symbol_match;
    std::regex symbol_regex(regex);

    for (int line_number = 0; line_number < lines.size(); line_number++) {
        string line = lines[line_number];
        auto symbol_begin = std::sregex_iterator(line.begin(), line.end(), symbol_regex);
        auto symbol_end = std::sregex_iterator();

        for (std::sregex_iterator reg_it = symbol_begin; reg_it != symbol_end; ++reg_it) {
            std::smatch match = *reg_it;
            positions.push_back(SymbolLocation(line_number, match.position()));
        }
    }
    return positions;
}

vector<std::smatch> number_matches(const string& line) {
    vector<std::smatch> matches;

    // Regex setup
    std::smatch number_match;
    std::regex number_regex("\\d+");

    auto regex_begin = std::sregex_iterator(line.begin(), line.end(), number_regex);
    auto regex_end = std::sregex_iterator();

    for (std::sregex_iterator reg_it = regex_begin; reg_it != regex_end; ++reg_it) {
        matches.push_back(*reg_it);
    }
    return matches;
}

bool is_part_number(const std::smatch& match, int line_number,
                    vector<SymbolLocation>& symbol_positions) {
    int match_begin = match.position();
    int match_end = match.position() + match.length() - 1;

    for (auto& symbol_position : symbol_positions) {
        // Only consider symbols that are between one line above and one below
        if ((abs(line_number - symbol_position.line) > 1)) {
            continue;
        }

        // Should match every combination
        if (abs(int(match_begin - symbol_position.position)) <= 1 ||
            abs(int(match_end - symbol_position.position)) <= 1) {
            return true;
        }
    }
    return false;
}

vector<int> find_part_numbers(const vector<string>& lines) {
    vector<int> part_numbers;
    auto symbol_positions = find_symbol_positions(lines);

    for (int line_number = 0; line_number < lines.size(); line_number++) {
        string line = lines[line_number];
        auto matches = number_matches(line);

        for (auto& match : matches) {
            if (is_part_number(match, line_number, symbol_positions))
                part_numbers.push_back(std::stoi(match.str()));
        }
    }
    return part_numbers;
}

bool is_adjacent(std::smatch number_match, SymbolLocation symbol_position) {
    int match_begin = number_match.position();
    int match_end = number_match.position() + number_match.length() - 1;

    // Should match every combination
    if (abs(int(match_begin - symbol_position.position)) <= 1 ||
        abs(int(match_end - symbol_position.position)) <= 1) {
        return true;
    }

    return false;
}

vector<int> calculate_gear_ratios(const vector<string>& lines) {
    vector<int> result;

    // All occurrences of '*'
    auto potential_locations = find_symbol_positions(lines, "\\*");

    for (auto& location : potential_locations) {
        // Only consider gears with exactly 2 adjacent numbers
        int counter = 0;
        std::array<int, 2> adjacent_numbers{0, 0};

        auto surrounding_lines = {lines[location.line - 1], lines[location.line],
                                  lines[location.line + 1]};

        for (auto& line : surrounding_lines) {
            auto numbers = number_matches(line);

            for (auto& number_match : numbers) {
                if (is_adjacent(number_match, location)) {
                    if (counter < 2) {
                        adjacent_numbers[counter] = std::stoi(number_match.str());
                    }
                    counter++;
                }
            }
        }
        result.push_back(adjacent_numbers[0] * adjacent_numbers[1]);
    }

    return result;
}

int main() {
    string filename = "data/input.txt";

    int expected = 467835;
    int result = 0;

    vector<string> lines = read_inputs(filename);

    auto part_numbers = find_part_numbers(lines);
    auto gear_ratios = calculate_gear_ratios(lines);

    for (auto& x : gear_ratios) {
        result += x;
    }

    cout << "Result: " << result << endl;
}
