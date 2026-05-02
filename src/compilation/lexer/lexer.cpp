#include <cctype>

#include "lexer.h"
#include "lexer_constants.h"

// primary tokenizer
std::vector<Token> Lexer::tokenize() {    
    while (position < input.length()) {
        char current = peek();
        
        if (std::isalpha(current)) tokens.push_back(readIdentifierOrKeyword());
        else hopLine();
    }

    return tokens;
}

// utilities 
void Lexer::hopLine(int amount) {
    position += amount;
    column = 1;
    line += 1;
}

bool Lexer::withinBounds() {
    return position < static_cast<int>(input.size());
}

char Lexer::peek() {
    return withinBounds() ? input[position] : '\0';
}

// readers 
Token Lexer::readIdentifierOrKeyword() {
    Token token;
    std::string buffer;

    while (withinBounds() && std::isalnum(peek())) {
        buffer.push_back(peek());
        position++;
        column++;
    }

    if(LexerConstants::keywords.count(buffer)) {
        token.tokenType = LexerConstants::keywords.at(buffer);
    } else {
        token.tokenType = TokenType::identifier;
        token.value = buffer;
    }

    return token;
}