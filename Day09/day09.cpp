#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using std::istringstream;


// Data structure to store locations and their neighbors
// Probably won't even be needing this, keeping it, for now
struct node {
    std::pair<std::string, std::string> neighbors_pair;
    int distance;
};


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


// Builds a node with the neighbors data so it is easier to work with
node make_node(std::vector<std::string> line) {
    // neighbors= {{line.front(), line.at(2)}, 2};
    return {{line.front(), line.at(2)}, 2};
}


// Checks vector of strings for a 'search'. Returns true if search exists in the vector
bool contains_element(std::vector<std::string> str_vec, std::string search) {
    if (std::find(str_vec.begin(), str_vec.end(), search) != str_vec.end())
        return true;
    return false;
}


void build_map(std::unordered_map<std::string, std::vector<std::string>>& map, std::vector<std::string> line) {


}


int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day09 [input]\n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        std::string line;

        std::vector<std::string> splitted_line;
        std::unordered_map<std::string, std::vector<std::string>> locations;

        while (std::getline(input, line)) {
            // std::cout << line << std::endl;
            splitted_line = split(line);
        }

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
