#include <algorithm>
#include <iostream>
#include <fstream>
#include <tuple>
#include <set>
#include <vector>


std::tuple<int, int> new_position(char step, std::tuple<int, int> position) {
    if (step == '^') {
        std::get<1>(position) += 1;
    }
    else if (step == 'v') {
        std::get<1>(position) -= 1;
    }
    else if (step == '>') {
        std::get<0>(position) += 1;
    }
    else if (step == '<') {
        std::get<0>(position) -= 1;
    }

    return position;
}


int main(int argc, char *argv[]) {

    std::set<std::tuple<int, int>> houses;

    if (argc != 2) {
        std::cout << "Usage: ./day03 [input] \n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        std::string instructions;
        std::getline(input, instructions);

        std::tuple<int, int> current_santa = {0, 0};
        std::tuple<int, int> current_robot = {0, 0};
        houses.insert({0, 0});

        for (int turn = 0; auto &step: instructions) {
            if (turn == 0) {
                current_santa = new_position(step, current_santa);
                houses.insert(current_santa);
                turn = 1;
            }
            else {
                current_robot = new_position(step, current_robot);
                houses.insert(current_robot);
                turn = 0;
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
