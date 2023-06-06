#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <string>
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

// Checks vector of strings for a 'search'. Returns true if search exists in the vector
bool contains_element(std::vector<std::string> str_vec, std::string search) {
    if (std::find(str_vec.begin(), str_vec.end(), search) != str_vec.end())
        return true;
    return false;
}

std::string calculate(std::string& str) {
    std::map<char, std::vector<char>> map;
    std::string result;

    for (int i = 0, n = (int) str.length(); i < n; i ++) {
        int count = 1;
        char curr = str[i];

        while(i + 1 < n && str[i + 1] == curr) {
            i++;
            count++;
        }
        // result = result + (char) count;
        // result = result + curr;
        result.push_back((char) count);
        result.push_back(curr);
    }
    return result;

    // for (const auto& [key, values] : map) {
    //     std::cout << key << ": ";
    //     for (const auto& val : values) {
    //         std::cout << val << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // return "niggers";
}


int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day10 [input]\n";
        return 1;
    }
    std::string input = argv[1];

    // std::cout << calculate(input) << std::endl;
    //
    for (int i = 0; i < 40; i++) {
        input = calculate(input);
    }
    std::cout << input.length() << std::endl;

    return 0;
}
