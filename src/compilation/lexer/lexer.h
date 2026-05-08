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
            char spy();
            bool withinBounds(int = 0); // may just want a withinSpyBounds();

            bool isNewLine();
            bool isWhiteSpace();
            bool isDateLiteral(char);
            bool isStringDelimiter(char);
            bool isSeparator(char);

            void hop(int = 1);
            void advanceLine();
            
            Token readIdentifierOrKeyword();
            Token readStringLiteral();
            Token readDateLiteral();
            Token readSeparator();
            
        public:
            Lexer(const std::string& input) : input(input) {}
            std::vector<Token> tokenize();
    };
