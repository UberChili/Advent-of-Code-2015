#include <algorithm>
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

void update_map(std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph, std::vector<std::string> line) {
    graph[line.front()][line.at(2)] = static_cast<int>(std::stoul(line.back()));
    graph[line.at(2)][line.front()] = static_cast<int>(std::stoul(line.back()));
}


bool pair_compare(std::pair<std::string, int> a, std::pair<std::string, int> b) {
    return a.second < b.second;
}


std::string get_cheapest(std::unordered_map<std::string, int> map) {
    const auto result = std::min_element(map.begin(), map.end(), pair_compare);
    std::cout << "Min element is: " << result->first << " with val: " << result->second << std::endl;

    return result->first;
}


void printpath(std::unordered_map<std::string, std::unordered_map<std::string, int>> graph, std::string start) {
    // std::deque<std::string> search_queue;
    int total = 0;
    std::vector<std::string> searched;
    searched.push_back(start);

    for (const auto& [key, val] : graph) {
        std::cout << key << ": \n";
        std::string current = get_cheapest(val);
        if (!contains_element(searched, current)) {
            total += graph[key][current];
            searched.push_back(current);
        }
    }

    std::cout << "\nRoute: \n";
    for (const auto& i : searched) {
        std::cout << i << " ";
    }
    std::cout << "\nDistance: " << total << std::endl;

}


int main(int argc, char *argv[]){
    if (argc != 3) {
        std::cout << "Usage: ./day09 [input] [start]\n";
        return 1;
    }
    std::string start = argv[2];

    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        std::string line;

        std::vector<std::string> splitted_line;
        // std::unordered_map<std::string, location> locations;
        std::unordered_map<std::string, std::unordered_map<std::string, int>> locations;

        while (std::getline(input, line)) {
            // std::cout << line << std::endl;
            splitted_line = split(line);
            update_map(locations, splitted_line);
        }

        // for (const auto& [key, values] : locations) {
        //     std:: cout << key << ": ";
        //     for (const auto& val : values) {
        //         std::cout << val.second << " ";
        //     }
        //     std::cout << std::endl;
        // }
        printpath(locations, start);

        // for (const auto& [key, values] : locations) {
        //     std:: cout << key << ": ";
        //     for (const auto& val : values.neighbors) {
        //         std::cout << val.first << " ";
        //     }
        //     std::cout << std::endl;
        // }

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
