#pragma once

#include "tokens.h"
#include "program_node.h"

class Parser {
    public:
        explicit Parser(std::vector<Token> tokens);
        
        ProgramNode parseProgram();
        
    private:
        std::vector<Token> tokens;
        std::size_t position = 0;

        const Token& current();
        const Token& previous();
        const Token& advance();
        const Token& consume(TokenType, const std::string&);

        void setNodeSource(const Token&, const Token&, StatementNode&);

        bool isAtEnd();
        bool check(TokenType);
        bool match(TokenType);

        std::unique_ptr<StandupNode> parseStandup();
        std::unique_ptr<StatementNode> parseStatement();
        std::unique_ptr<DateStatementNode> parseDateStatement();
        std::unique_ptr<TagStatementNode> parseTagStatement();
        std::unique_ptr<AttendeeStatementNode> parseAttendeeStatement();
        std::unique_ptr<SummaryStatementNode> parseSummaryStatement();
        std::unique_ptr<SectionStatementNode> parseSectionStatement();
        std::unique_ptr<NoteStatementNode> parseNoteStatement();
        std::unique_ptr<DecisionStatementNode> parseDecisionStatement();
        std::unique_ptr<TodoStatementNode> parseTodoStatement();
        std::unique_ptr<BlockerStatementNode> parseBlockerStatement();
        std::unique_ptr<RiskStatementNode> parseRiskStatement();
        std::unique_ptr<LinkStatementNode> parseLinkStatement();

        std::string parsePriority();
};