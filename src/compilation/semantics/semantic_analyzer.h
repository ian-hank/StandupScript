#pragma once

#include <vector>

#include "program_node.h"
#include "semantic_error.h"

class SemanticAnalyzer {
    public:
        SemanticAnalyzer(const ProgramNode& programNode) : program(programNode) {}

        bool analyzeProgram();
        std::vector<SemanticError> getErrors();

    private:
        const ProgramNode& program;
        std::vector<SemanticError> errors;
        
        // primary block-nodes
        void analyzeStandup(const StandupNode& standup);
        void analyzeStatement(const StatementNode& statement);
        void analyzeSection(const SectionStatementNode& section);

        // virtuals
        void analyzeDate(const DateStatementNode& date);
        void analyzeTag(const TagStatementNode& tag);
        void analyzeAttendee(const AttendeeStatementNode& attendee);
};