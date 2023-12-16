#include <algorithm>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::size_t;
using std::string;

// Create map of string digits to the corresponding integers
map<string, int> digits_map{
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

void print_file(const string &filename) {
    std::ifstream infile(filename);
    string line;
    while (std::getline(infile, line)) {
        cout << line << endl;
    }
}

int convert_char_to_int(const char &c) { return int(c) - int('0'); }

// Replace instances of string digits with their integer counterparts
void replace_first_string_digit(string &line) {
    std::size_t smallest_pos = line.length();
    string digit_to_replace;

    for (map<string, int>::iterator it = digits_map.begin(); it != digits_map.end(); ++it) {
        string cur_digit = it->first;
        size_t digit_pos = line.find(cur_digit);
        if (digit_pos < smallest_pos) {
            smallest_pos = digit_pos;
            digit_to_replace = cur_digit;
        }
    }
    if (smallest_pos < line.length()) {
        line.replace(smallest_pos, digit_to_replace.length(),
                     std::to_string(digits_map[digit_to_replace]));
    }
}

void replace_last_string_digit(string &line) {
    size_t largest_pos = 0;
    string digit_to_replace;

    for (map<string, int>::iterator it = digits_map.begin(); it != digits_map.end(); ++it) {
        string cur_digit = it->first;
        size_t digit_pos = line.rfind(cur_digit);
        if (digit_pos > largest_pos && digit_pos < line.length()) {
            largest_pos = digit_pos;
            digit_to_replace = cur_digit;
        }
    }

    // If largest_pos = 0, this should be handled by replace_first_string_digit()
    if (largest_pos > 0) {
        line.replace(largest_pos, digit_to_replace.length(),
                     std::to_string(digits_map[digit_to_replace]));
    }
}

int get_first_digit(const string &line) {
    string line_copy{line};
    replace_first_string_digit(line_copy);

    // Return first digit encountered
    for (auto &c : line_copy) {
        if (std::isdigit(c)) {
            return (convert_char_to_int(c));
        }
    }
    throw std::runtime_error("No digit found in the line.");
}

int get_last_digit(const string &line) {
    string line_copy{line};
    replace_last_string_digit(line_copy);
    std::reverse(line_copy.begin(), line_copy.end());

    // Return first digit encountered
    for (auto &c : line_copy) {
        if (std::isdigit(c)) {
            return (convert_char_to_int(c));
        }
    }
    throw std::runtime_error("No digit found in the line.");
}

int get_calibration_value(string &line) {
    // Construct 2-digit number from first and last digits
    int result = 10 * get_first_digit(line) + get_last_digit(line);
    return result;
}

int main() {
    string input_file = "data/day1-input.txt";
    // string input_file = "data/example.txt";
    std::ifstream infile(input_file);

    int result = 0;

    string line;
    while (std::getline(infile, line)) {
        result += get_calibration_value(line);
    }

    cout << "result = " << result << endl;
    return 0;
}
