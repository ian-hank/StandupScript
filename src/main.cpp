#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "StandupScript Error: Unknown usage... (expecting): standupc <file.stup>" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cout << "StandupScript Error: Unable to open input file" << std::endl;
        return EXIT_FAILURE;
    }

    std::stringstream contents_stream;
    contents_stream << input_file.rdbuf();
    std::string contents = contents_stream.str();

    return EXIT_SUCCESS;
}