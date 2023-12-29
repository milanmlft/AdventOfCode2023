#include <exception>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

void remove_prefix(string& line) { line.erase(0, line.find(":") + 1); }

int n_matches(string& line) {
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

    return matches;
}

// Part 2
int n_total_cards(std::ifstream& input) {
    vector<int> card_copies{1};
    string line;
    int current_card = 0;
    while (std::getline(input, line)) {
        // Initialise if current card doesn't exist yet
        if (current_card > card_copies.size() - 1) {
            card_copies.push_back(1);
        }

        int n_matching_numbers = n_matches(line);
        for (int i = 1; i <= n_matching_numbers; i++) {
            int next_card = current_card + i;
            // Initialise if entry doesn't exist yet
            if (next_card > card_copies.size() - 1) {
                card_copies.push_back(1);
            }
            card_copies.at(next_card) += card_copies.at(current_card);
        }
        current_card++;
    }

    // Sum up all elements in card_copies
    return std::reduce(card_copies.begin(), card_copies.end());
}

int main() {
    std::ifstream infile("data/input.txt");
    cout << "Result: " << n_total_cards(infile) << endl;
}
