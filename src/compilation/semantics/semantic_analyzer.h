#pragma once

#include "program_node.h"

class SemanticAnalyzer {
    public:
        SemanticAnalyzer(const ProgramNode& programNode) : program(programNode) {}

        void analyzeProgram();

    private:
        const ProgramNode& program;
        
        void analyzeStandup(const StandupNode& standup);
        void analyzeStatement(const StatementNode& statement);
        void analyzeSection(const SectionStatementNode& section);
};