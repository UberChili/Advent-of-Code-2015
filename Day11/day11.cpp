#include <iostream>
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


void increment(std::string str) {
    std::string result;
    // char curr;

    for (int i = (int) str.length() - 1; i >= 0; i--) {
        // curr = str[i] + 1;
        // result.insert(result.begin(), curr);
        if (str[i] + 1 == 123) {
            str[i] = 97;
        }
    }
    // std::cout << result << std::endl;
    std::cout << str << std::endl;
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day11 [input]\n";
        return 1;
    }
    std::string text = argv[1];

    increment(text);

    // std::cout << increment(text) << std::endl;

    return 0;
}
