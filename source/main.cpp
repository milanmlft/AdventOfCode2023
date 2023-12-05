#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int convert_char_to_int(const char &c) { return int(c) - int('0'); }

int get_calibration_value(const string &line) {
int get_calibration_value(string &line) {
    vector<int> digits;

    string::iterator it;
    for (it = line.begin(); it < line.end(); it++) {
        if (std::isdigit(*it)) {
            digits.push_back(convert_char_to_int(*it));
        }
    }

    // Construct 2-digit number from first and last digits
    return 10 * digits[0] + digits[digits.size() - 1];
}

int main() {
    string input_file = "data/day1-input.txt";

    std::ifstream infile(input_file);

    int result = 0;

    string line;
    while (std::getline(infile, line)) {
        result += get_calibration_value(line);
    }

    cout << "result = " << result << endl;

    return 0;
}
