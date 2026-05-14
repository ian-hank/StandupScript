#pragma once

#include "tokens.h"
#include "program_node.h"

class Parser {
    private:
        std::vector<Token> tokens;
        std::size_t position = 0;

        const Token& current();
        const Token& previous();
        const Token& advance();
        const Token& consume(TokenType, const std::string&);

        bool isAtEnd();
        bool check(TokenType);
        bool match(TokenType);

    public:
        explicit Parser(std::vector<Token> tokens);

        ProgramNode parseProgram();
        StandupNode parseStandup();

        std::unique_ptr<StatementNode> parseStatement();
        std::unique_ptr<DateStatementNode> parseDateStatement();
        std::unique_ptr<TagStatementNode> parseTagStatement();
        std::unique_ptr<AttendeeStatementNode> parseAttendeeStatement();
        std::unique_ptr<SummaryStatementNode> parseSummaryStatement();
};