// Opening parenthesis '(' means going up one floor
// Closing parenthesis ')' means going down one floor

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>


int main(int argc, char *argv[]){

    if (argc != 2) {
        std::cout << "Usage: ./day01 [input] \n";
        return 1;
    }

    double floor = 0;
    std::string contents;
    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        std::getline(input, contents);

        bool found = false;
        for (int index = 1; auto &i : contents) {
            if (i == '(') {
                floor += 1;
            }
            else if (i == ')') {
                floor -= 1;
            }

            if (floor == -1 && found != true) {
                // int index = std::distance(contents.begin(), std::find(contents.begin(), contents.end(), i)) + 1;
                int index = &i - &contents[0];
                std::cout << "First position that takes to basement: "
                          << index + 1
                          << std::endl;
                found = true;
            }
            index += 1;
        }

        std::cout << "Floor: " << floor << std::endl;
        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
