#include <cstring>
#include <deque>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>


// Checks vector of strings for a 'search'. Returns true if search exists in the vector
bool contains_element(std::vector<std::string> str_vec, std::string search) {
    if (std::find(str_vec.begin(), str_vec.end(), search) != str_vec.end())
        return true;
    return false;
}


bool person_is_seller(std::string str) {
    if (str.back() == 'm')
        return true;
    return false;
}


bool search(std::unordered_map<std::string, std::vector<std::string>> graph, std::string name) {
    std::deque<std::string> search_queue;
    std::vector<std::string> searched;
    search_queue.insert(search_queue.end(), graph[name].begin(), graph[name].end());

    while (!search_queue.empty()) {
        std::string person = search_queue.front();
        search_queue.pop_front();
        if (!contains_element(searched, person)) {
            if (person_is_seller(person)) {
                std::cout << person << " is a mango seller!\n";
                return true;
            }
            else {
                search_queue.insert(search_queue.end(), graph[person].begin(), graph[person].end());
                searched.push_back(person);
            }
        }
    }
    return false;
}


int main(void){
    std::unordered_map<std::string, std::vector<std::string>> map;

    map["you"] = {"alice", "bob", "claire"};
    map["bob"] = {"anuj", "peggy"};
    map["alice"] = {"peggy"};
    map["claire"] = {"thom", "johnny"};
    map["anuj"] = {};
    map["peggy"] = {};
    map["thom"] = {};
    map["johnny"] = {};

    search(map, "you");


    return 0;
}
