#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>
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
    return (int) line.length();
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


// int count_ocurrences(const std::string& str, const std::string& regexPattern) {
//     std::regex regexObj(regexPattern);
//     std::smatch match;
//     std::string::const_iterator searchStart(str.cbegin());
//     int count = 0;

//     while (std::regex_search(searchStart, str.cend(), match, regexObj)) {
//         count++;
//         searchStart = match.suffix().first;
//     }

//     return count;
// }


// int get_backslashes(std::string line) {
//     return count_ocurrences(line, "\\\\\\\\");
// }


// int get_quotes(std::string line) {
//     return count_ocurrences(line, "\\\\\\\"");
// }


// int get_hexadecimals(std::string line) {
//     return (count_ocurrences(line, "\\\\x[0-9a-f]{2}") * 3);
// }


int get_characters_in_memory(std::string line) {
    int counter = 0;

    for (int i = 0, len = (int) line.length(); i < len; i++) {
        if (line[i] == '\\') {
            if (line[i + 1] == '\\') {
                i += 1;
            }
            else if (line[i + 1] == '"') {
                i += 1;
            }
            else if (line[i + 1] == 'x') {
                i += 3;
            }
        }
        counter++;
    }
    return counter - 2;
}


int encode(std::string line) {
    std::string out_str;

    out_str.push_back('"');
    for (int i = 0, len = (int) line.length(); i < len; i++) {
        if (line[i] == '"') {
            out_str.push_back('\\');
        }
        else if (line[i] == '\\') {
            out_str.push_back('\\');
        }
        out_str.push_back(line[i]);
    }
    out_str.push_back('"');

    std::cout << out_str << std::endl;
    return (int) out_str.length();
}


int get_total_cm(std::vector<std::string>& lines) {
    int sum = 0;

    for (const auto& line : lines) {
        // std::cout << "SL: " << get_string_literals(line) << std::endl;
        sum += get_characters_in_memory(line);
    }

    return sum;
}


int get_total_encoded(std::vector<std::string>& lines) {
    int sum = 0;

    for (const auto& line : lines) {
        // std::cout << "SL: " << get_string_literals(line) << std::endl;
        sum += encode(line);
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
            contents.push_back(line);

            std::cout << line << std::endl;
            std::cout << "SL: " << get_string_literals(line) << std::endl;
            // std::cout << "CM: " << get_characters_in_memory(line) << std::endl;
            std::cout << "Encoded: " << encode(line) << std::endl;
        }
        std::cout << "total number of characters of string code: " << get_total_sc(contents) << std::endl;
        // std::cout << "total number of characters in memory: " << get_total_cm(contents) << std::endl;

        int total_sc = get_total_sc(contents);
        // int total_cm = get_total_cm(contents);
        int total_encoded= get_total_encoded(contents);

        // std::cout << "Total SC: " << total_sc << " Total CM: " << total_cm << " Result: " << total_sc - total_cm << std::endl;
        std::cout << "Total SC: " << total_sc << " Total Encoded: " << total_encoded << " Result: " << total_encoded - total_sc << std::endl;

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
