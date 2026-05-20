#include <cctype>
#include <iostream>
#include <regex>

#include "lexer.h"
#include "lexer_constants.h"

const bool LEXER_DEBUG = true;

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

    Token token = completeToken(TokenType::eof);
    tokens.push_back(token);

    return tokens;
}

char Lexer::peek() {
    return withinBounds() 
        ? input[position] 
        : '\0';
}

char Lexer::spy() {
    return withinBounds(1) 
        ? input[position + 1] 
        : '\0';
}

SourceLocation Lexer::currentLocation() {
    return {
        .line = line,
        .column = column
    };
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

Token Lexer::startToken() {
    Token token;
    token.location.start = currentLocation();

    return token;
}

Token Lexer::startToken(TokenType tokenType) {
    Token token = startToken();
    token.tokenType = tokenType;

    return token;
}

void Lexer::finishToken(Token& token) {
    token.location.end = currentLocation();
}

Token Lexer::completeToken(TokenType tokenType) {
    Token token = startToken();
    token.tokenType = tokenType;
    finishToken(token);

    return token;
}


Token Lexer::readIdentifierOrKeyword() {
    Token token = startToken();
    std::string buffer;
    while (withinBounds() && std::isalnum(peek())) {
        buffer.push_back(peek());
        hop();
    }

    if (LexerConstants::keywords.count(buffer)) {
        token.tokenType = LexerConstants::keywords.at(buffer);
        finishToken(token);

        return token;
    }

    token.value = buffer;
    token.tokenType = TokenType::identifier;
    finishToken(token);

    return token;
}

Token Lexer::readStringLiteral() {
    Token token = startToken(TokenType::lit_string);
    hop();
    
    if (input.find('\"', position) == std::string::npos) {
        std::cerr 
            << "StandupScript Error (lexer): String is never closed" 
            << " at line " << line 
            << ", column " << column;
        exit(EXIT_FAILURE);
    }

    std::string buffer;
    while (peek() != '\"') {
        buffer.push_back(peek());
        hop();
    }

    token.value = buffer;
    hop();
    finishToken(token);

    return token;
}

Token Lexer::readDateLiteral() {
    Token token = startToken(TokenType::lit_date);
    token.value = input.substr(position, 10);
    hop(10);
    finishToken(token);

    return token;
}

Token Lexer::readSeparator() {
    Token token = startToken();
    token.tokenType = LexerConstants::separators.at(peek());
    hop();
    finishToken(token);

    return token;
}