#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using std::istringstream;


// splits a string by whitespaces and returns a vector of strings
std::vector<std::string> split(std::string line) {
    std::vector<std::string> tokens;
    istringstream iss(line);
    std::string token;


    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}


int get_string_literals(std::string line) {
    int counter;
    counter = (int) line.length();
    return counter;
}


// returns the total number of characters of string code
int get_total_sc(std::vector<std::string>& lines) {
    int sum = 0;

    for (const auto& line : lines) {
        // std::cout << "SL: " << get_string_literals(line) << std::endl;
        sum += get_string_literals(line);
    }

    return sum;
}


bool contains(const std::string& str, const std::string& substring) {
    return str.find(substring) != std::string::npos;
}


int get_characters_in_memory(std::string line) {

    int counter = (int) line.length();;

    for (int i = 0, len = (int) line.length(); i < len; i++) {
        if (line[i] == '\\') {
            if (line[i + 1] == 'x') {
                counter = counter - 3;
            }
            else if (line[i + 1] == '"') {
                counter = counter - 1;
            }
            else if (line[i + 1] == '\\') {
                counter = counter - 1;
            }
        }
    }

    return counter - 2;
}


int get_total_cm(std::vector<std::string>& lines) {
    int sum = 0;

    for (const auto& line : lines) {
        sum += get_characters_in_memory(line);
    }

    return sum;
}


int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day08 [input]\n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        std::string line;

        std::vector<std::string> contents;
        while (std::getline(input, line)) {
            std::cout << "CiM: " << get_characters_in_memory(line) << std::endl;
            contents.push_back(line);

            // std::cout << line << std::endl;
            // std::cout << "SL: " << get_string_literals(line) << std::endl;
        }
        // std::cout << "total number of characters of string code: " << get_total_sc(contents) << std::endl;
        // std::cout << "total number of characters in memory: " << get_total_cm(contents) << std::endl;

        int total_sc = get_total_sc(contents);
        int total_cm = get_total_cm(contents);

        std::cout << "Total SC: " << total_sc << " Total CM: " << total_cm << " Result: " << total_sc - total_cm << std::endl;

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
