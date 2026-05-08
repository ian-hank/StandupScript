#include <cctype>
#include <iostream>
#include <regex>

#include "lexer.h"
#include "lexer_constants.h"

const bool LEXER_DEBUG = true;

// primary tokenizer
std::vector<Token> Lexer::tokenize() {    
    while (withinBounds()) {
        if (isNewLine()) {
            advanceLine();
            continue;
        }

        if (isWhiteSpace()) {
            hop();
            continue;
        }
        
        char current = peek();
        if (std::isalpha(current)) tokens.push_back(readIdentifierOrKeyword());
        else if (isDateLiteral(current)) tokens.push_back(readDateLiteral());
        else if (isStringDelimiter(current)) tokens.push_back(readStringLiteral());
        else if (isSeparator(current)) tokens.push_back(readSeparator());
        else {
            std::cerr 
                << "StandupScript Error (lexer): Unrecognized character '" << current 
                << "' at line " << line 
                << ", column " << column;
            exit(EXIT_FAILURE);
        }
    }

    return tokens;
}

// utilities 
char Lexer::peek() {
    return withinBounds() ? input[position] : '\0';
}

char Lexer::spy() {
    return withinBounds(1) ? input[position + 1] : '\0';
}

void Lexer::hop(int amount) {
        position += amount;
        column += amount;
}

void Lexer::advanceLine() {
    if (peek() == '\r' and spy() == '\n') {
        position += 2;
        line++;
        column = 1;
        return;
    }

    position++;
    line++;
    column = 1;
}

bool Lexer::withinBounds(int amount) {
    return (position + amount) < static_cast<int>(input.size());
}

bool Lexer::isNewLine() {
    char current = peek();

    if (current == '\n') {
        return true;
    } else if (current == '\r' and spy() == '\n') {
        return true;
    }

    return false;
}

bool Lexer::isWhiteSpace() {
    return std::isspace(peek());
}

bool Lexer::isDateLiteral(char current) {
    if (!std::isdigit(current)) {
        return false;
    }

    std::string date = input.substr(position, 10);
    std::regex datePattern(R"([0-9]{4}-[0-9]{2}-[0-9]{2})");
    if (!std::regex_match(date, datePattern)) {
        return false;
    }
    
    return true;
}

bool Lexer::isStringDelimiter(char current) {
    return current == '\"';
}

bool Lexer::isSeparator(char current) {
    return LexerConstants::separators.count(current);
}

// readers 
Token Lexer::readIdentifierOrKeyword() {
    Token token;
    std::string buffer;

    token.line = line;
    token.column = column;
    while (withinBounds() && std::isalnum(peek())) {
        buffer.push_back(peek());
        hop();
    }

    if (LexerConstants::keywords.count(buffer)) {
        token.tokenType = LexerConstants::keywords.at(buffer);
        return token;
    }

    token.tokenType = TokenType::identifier;
    token.value = buffer;
    return token;
}

Token Lexer::readStringLiteral() {
    Token token;
    std::string buffer;

    token.line = line;
    token.column = column;
    hop();
    
    if (input.find('\"', position) == std::string::npos) {
        std::cerr 
            << "StandupScript Error (lexer): String is never closed" 
            << " at line " << line 
            << ", column " << column;
        exit(EXIT_FAILURE);
    }

    while (peek() != '\"') {
        buffer.push_back(peek());
        hop();
    }

    hop();
    token.tokenType = TokenType::lit_string;
    token.value = buffer;

    return token;
}

Token Lexer::readDateLiteral() {
    Token token;

    token.line = line;
    token.column = column;
    token.tokenType = TokenType::lit_date;
    token.value = input.substr(position, 10);

    hop(10);
    return token;
}

Token Lexer::readSeparator() {
    Token token;
    token.line = line;
    token.column = column;
    token.tokenType = LexerConstants::separators.at(peek());

    hop();
    return token;
}