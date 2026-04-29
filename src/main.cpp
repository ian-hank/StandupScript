#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "StandupScript Error: Unknown usage... (expecting): standupc <input.stup>" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cout << "StandupScript Error: Unable to open input file" << std::endl;
        return EXIT_FAILURE;
    }
    
    return 0;
}