#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <tuple>
#include <vector>


std::tuple<int, int, int> get_dimensions(std::string);
std::vector<std::string> split(std::string input, std::string delimiter);


std::vector<std::string> split(std::string input, std::string delimiter) {

    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        tokens.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    tokens.push_back(input);

    return tokens;
}


std::tuple<int, int, int> get_dimensions(std::string box) {
    int length, width, height;

    std::vector<std::string> dimensions_vec = split(box, "x");

    if (dimensions_vec.size() != 3) {
        std::cout << "Error in tokens vector \n";
    }
    else {
        length = std::stoi(dimensions_vec[0]);
        width = std::stoi(dimensions_vec[1]);
        height = std::stoi(dimensions_vec[2]);
    }
    return {length, width, height};
}


int main(int argc, char *argv[]){

    if (argc != 2) {
        std::cout << "Usage: ./day02 [input] \n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        // std::getline(input, contents);

        int wrap_per_box, ribbon, bow, total_wrap = 0, total_ribbon = 0;
        int smallest, side0, side1, side2, length, width, height;
        std::string box;
        while(std::getline(input, box)) {

            std::vector<std::string> dims = split(box, "x");
            length = std::stoi(dims.at(0));
            width = std::stoi(dims.at(1));
            height = std::stoi(dims.at(2));

            side0 = length * width;
            side1 = width * height;
            side2 = height * length;

            bow = length * width * height;
            // ribbon = (length + length + width + width);
            ribbon = 2 * std::min({length + width, width + height, height + length});

            smallest = std::min({side0, side1, side2});
            wrap_per_box = ((2 * side0) + (2 * side1) + (2 * side2)) + smallest;

            total_wrap += wrap_per_box;
            total_ribbon += (ribbon + bow);

            std::cout << box
                      << " length: " << dims.at(0) << " "
                      << "width: " << dims.at(1) << " "
                      << "height: " << dims.at(2)
                      << " wrap per box: " << wrap_per_box
                      << " bow: " << bow << " "
                      << " ribbon: " << ribbon << std::endl;

        }
        std::cout << " -> Total wrap needed: " << total_wrap << std::endl;
        std::cout << " -> Total ribbon needed: " << total_ribbon << std::endl;

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
