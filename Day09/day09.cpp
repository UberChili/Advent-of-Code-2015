#include <cstring>
#include <deque>
#include <queue>
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
struct location {
    std::vector<std::pair<std::string, int>> neighbors;
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


// Checks vector of strings for a 'search'. Returns true if search exists in the vector
bool contains_element(std::vector<std::string> str_vec, std::string search) {
    if (std::find(str_vec.begin(), str_vec.end(), search) != str_vec.end())
        return true;
    return false;
}


void update_map(std::unordered_map<std::string, location>& map, std::vector<std::string> line) {
    map[line.front()].neighbors.push_back({line.at(2), static_cast<int>(std::stoul(line.back()))});
    map[line.at(2)].neighbors.push_back({line.front(), static_cast<int>(std::stoul(line.back()))});
}


void dijkstra(std::unordered_map<std::string, location> map, std::string start) {

    for (const auto& [key, value] : map) {
    }

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
        std::unordered_map<std::string, location> locations;

        while (std::getline(input, line)) {
            // std::cout << line << std::endl;
            splitted_line = split(line);
            update_map(locations, splitted_line);
        }


        for (const auto& [key, values] : locations) {
            std:: cout << key << ": ";
            for (const auto& val : values.neighbors) {
                std::cout << val.first << " ";
            }
            std::cout << std::endl;
        }

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
