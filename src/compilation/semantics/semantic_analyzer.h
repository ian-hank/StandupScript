#pragma once

#include <vector>
#include <unordered_map>
#include <set>

#include "program_node.h"
#include "semantic_error.h"
#include "attendee_symbol.h"

class SemanticAnalyzer {
    public:
        SemanticAnalyzer(const ProgramNode& programNode) : program(programNode) {}

        bool analyzeProgram();
        std::vector<SemanticError> getErrors();

    private:
        const ProgramNode& program;
        std::set<std::string> tags;
        std::vector<AttendeeInfo> attendees;
        std::unordered_map<std::string, int> attendeesByName;
        std::unordered_map<std::string, int> attendeesByAlias;
        std::vector<SemanticError> errors;

        SourceSpan getSourceSpan(const StatementNode& node);
        void addError(std::vector<SemanticError>& errors, std::string errorMessage, SemanticErrorCode errorCode, SourceSpan source);

        // primary block-nodes
        void analyzeStandup(const StandupNode& standup);
        void analyzeStatement(const StatementNode& statement);
        void analyzeSection(const SectionStatementNode& section);

        // virtuals
        void analyzeDate(const DateStatementNode& date);
        void analyzeTag(const TagStatementNode& tag);
        void analyzeAttendee(const AttendeeStatementNode& attendee);
        void analyzeSummary(const SummaryStatementNode& summary);
        void analyzeNote(const NoteStatementNode& note);
        void analyzeNDecision(const DecisionStatementNode& decision);
        void analyzeTodo(const TodoStatementNode& todo);
        void analyzeBlocker(const BlockerStatementNode& blocker);
        void analyzeRisk(const RiskStatementNode& risk);
        void analyzeLink(const LinkStatementNode& link);
};