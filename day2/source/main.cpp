#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Possible colors are red, blue and green
vector<string> colors{"red", "blue", "green"};

struct GameSet {
    int n_red;
    int n_blue;
    int n_green;

    int n_cubes(const string& color) {
        if (color == "red") {
            return n_red;
        } else if (color == "green") {
            return n_green;
        } else if (color == "blue") {
            return n_blue;
        } else {
            return 0;
        }
    }
};

struct Game {
    int ID;
    vector<GameSet> sets;

    int max_cubes(const string& color) {
        vector<int> all_cubes;
        for (auto& set : sets) {
            all_cubes.push_back(set.n_cubes(color));
        }
        return *std::max_element(all_cubes.begin(), all_cubes.end());
    }
};

vector<string> read_inputs(const string& filename) {
    // Read input file
    std::ifstream infile(filename);
    string line;
    vector<string> output;

    while (std::getline(infile, line)) {
        output.push_back(line);
    }
    return output;
}

vector<string> get_sets(string line) {
    vector<string> sets;
    string delimiter("; ");

    // Extract substrings from input line that end at 'delimiter'
    //   then remove the substring from the original line to handle the next substrings
    size_t pos{0};
    while ((pos = line.find(delimiter)) != line.npos) {
        sets.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
    }
    // Add rest of remaining line as last set
    sets.push_back(line);

    return sets;
}

int find_integer_from_pattern(const string& input, std::regex pattern) {
    int result = 0;
    std::smatch match;

    if (std::regex_search(input.begin(), input.end(), match, pattern)) {
        result = std::stoi(match[1]);
    }

    return result;
}

int parse_color(const string& input, string color) {
    int result;

    // Construct regex
    color.insert(0, "(\\d+)+ ");
    std::regex pattern(color);

    return find_integer_from_pattern(input, pattern);
}

GameSet parse_set(const string& input) {
    GameSet game_set;
    game_set.n_red = parse_color(input, "red");
    game_set.n_blue = parse_color(input, "blue");
    game_set.n_green = parse_color(input, "green");
    return game_set;
}

Game parse_game(const string& line) {
    Game game;

    // Get the Game ID
    std::regex pattern("Game ((\\d)+): ");
    game.ID = find_integer_from_pattern(line, pattern);

    // Remove the Game ID pattern (Game \\d: ) from the input line
    string new_line = std::regex_replace(line, pattern, "");

    // Get the game sets
    vector<string> sets = get_sets(new_line);
    for (auto& set : sets) {
        game.sets.push_back(parse_set(set));
    }

    return game;
}

int main() {
    string filename("data/input.txt");
    vector<string> lines(read_inputs(filename));

    int total_red = 12;
    int total_green = 13;
    int total_blue = 14;

    int result = 0;

    for (auto& line : lines) {
        Game game = parse_game(line);

        int max_red = game.max_cubes("red");
        int max_green = game.max_cubes("green");
        int max_blue = game.max_cubes("blue");

        // Check if game is possible
        if (max_red <= total_red && max_green <= total_green && max_blue <= total_blue) {
            cout << "Game " << game.ID << " is possible" << endl;
            result += game.ID;
        }
    }

    cout << "Result: " << result << endl;
}
