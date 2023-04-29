#include <algorithm>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>


int main(int argc, char *argv[]){

    std::vector<std::tuple<int, int>> houses;

    if (argc != 2) {
        std::cout << "Usage: ./day03 [input] \n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        std::string instructions;
        std::getline(input, instructions);

        std::tuple<int, int> current = {0, 0};
        houses.push_back(current);

        for (auto &step: instructions) {
            if (step == '^') {
                std::get<1>(current) += 1;

                if (std::find(houses.begin(), houses.end(), current) != houses.end()) {
                    continue;
                }
                else {
                    houses.push_back(current);
                }
            }
            else if (step == 'v') {
                std::get<1>(current) -= 1;
                if (std::find(houses.begin(), houses.end(), current) != houses.end()) {
                    continue;
                }
                else {
                    houses.push_back(current);
                }
            }
            if (step == '>') {
                std::get<0>(current) += 1;
                if (std::find(houses.begin(), houses.end(), current) != houses.end()) {
                    continue;
                }
                else {
                    houses.push_back(current);
                }
            }
            if (step == '<') {
                std::get<0>(current) -= 1;
                if (std::find(houses.begin(), houses.end(), current) != houses.end()) {
                    continue;
                }
                else {
                    houses.push_back(current);
                }
            }
        }
        std::cout << "Houses that got at least one gift: " << houses.size() << std::endl;

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
