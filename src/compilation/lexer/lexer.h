    #pragma once

    #include <string>
    #include <vector>

    #include "tokens.h"

    class Lexer {
        private:
            std::string input;
            int position = 0;
            int line = 1;
            int column = 1;
            std::vector<Token> tokens;

            char peek();
            bool withinBounds();
            void hopLine(int amount = 1);
            
            Token readIdentifierOrKeyword();
            
        public:
            Lexer(const std::string& input) : input(input) {}
            std::vector<Token> tokenize();
    };
