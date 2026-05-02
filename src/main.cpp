#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "lexer.h"
#include "token_utils.h"

const bool LEXER_DEBUG = true;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "StandupScript Error: Invalid usage.\nUsage: standupc <file.stup>" << std::endl;
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

    Lexer lexer(std::move(contents));
    std::vector<Token> tokens;
    try {
        tokens = lexer.tokenize();
        if (LEXER_DEBUG) {
            TokenUtils::printTokens(tokens);
        }
    } catch(const std::exception& e) {
        std::cerr << "StandupScript Error (lexing): " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}