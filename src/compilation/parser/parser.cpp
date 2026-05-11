#include "parser.h"
#include "parse_error.h"

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

ProgramNode Parser::parseProgram() {
    ProgramNode pNode;
    pNode.standup = parseStandup();

    consume(TokenType::eof, "Expected end of file after standup block.");
}

StandupNode Parser::parseStandup() {
    consume(
        TokenType::kw_standup, 
        "Expected 'standup' keyword to begin file."
    );

    const Token& titleToken = consume(
        TokenType::lit_string, 
        "Expected string literal after 'standup' keyword."
    );

    consume(
        TokenType::left_curly_bracket,
        "Exepcted '{' folowing standup title."
    );

    StandupNode sNode;
    sNode.title = titleToken.value.value_or("");

    while (!check(TokenType::right_curly_bracket) && !isAtEnd()) {
        //sNode.statements.push_back(parseStatement());
    }
}

const Token& Parser::current() {
    return tokens[position];
}

const Token& Parser::previous() {
    return tokens[position - 1];
}

const Token& Parser::advance() {
    if (!isAtEnd()) {
        position++;
    }

    return previous();
}

const Token& Parser::consume(TokenType tokenType, const std::string& message) {
    if (check(tokenType)) {
        return advance();
    }

    throw ParseError(message, current().line, current().column);
}

bool Parser::isAtEnd() {
    return current().tokenType == TokenType::eof;
}

bool Parser::check(TokenType tokenType) {
    if (isAtEnd()) {
        return false;
    }

    return current().tokenType == tokenType;
}

bool Parser::match(TokenType tokenType) {
    if (!check(tokenType)) {
        return false;
    }

    advance();
    return true;
}
