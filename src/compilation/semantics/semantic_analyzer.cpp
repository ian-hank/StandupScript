#include <sstream>

#include "semantic_analyzer.h"

bool SemanticAnalyzer::analyzeProgram() {
    analyzeStandup(program.standup);

    return errors.empty();
}

std::vector<SemanticError> SemanticAnalyzer::getErrors() {
    return errors;
}

void SemanticAnalyzer::analyzeStandup(const StandupNode& standup) {
    for (const auto& statement : standup.statements) {
        analyzeStatement(*statement);
    }
}

void SemanticAnalyzer::analyzeStatement(const StatementNode& statement) {
    if (const auto* sectionStatement = dynamic_cast<const SectionStatementNode*>(&statement)) {
        analyzeSection(*sectionStatement);
    } else if (const auto* dateStatement = dynamic_cast<const DateStatementNode*>(&statement)) {
        analyzeDate(*dateStatement);
    } /*else if (const auto* tagStatement = dynamic_cast<const TagStatementNode*>(&statement)) {
        analyzeTag(*tagStatement);
    } else if (const auto* attendeeStatement = dynamic_cast<const AttendeeStatementNode*>(&statement)) {
        analyzeAttendee(*attendeeStatement);
    } */
}

void SemanticAnalyzer::analyzeSection(const SectionStatementNode& section) {
    for (const auto& sectionStatement : section.statements) {
        analyzeStatement(*sectionStatement);
    }
}

void SemanticAnalyzer::analyzeDate(const DateStatementNode& date) {
    int DATE_LITERAL_MINIMUM_YEAR = 2000;
    int DATE_LITERAL_MAXIMUM_YEAR = 2100;
    int DATE_LITERAL_MINIMUM_MONTH = 1;
    int DATE_LITERAL_MAXIMUM_MONTH = 12;
    std::unordered_map<int, int> DATE_LITERAL_MAXIMUM_DAY = {
        {1, 31},
        {2, 28},
        {3, 31},
        {4, 30},
        {5, 31},
        {6, 30},
        {7, 31},
        {8, 31},
        {9, 30},
        {10, 31},
        {11, 30},
        {12, 31},
    };

    // no need to catch, we already validate this is an integer with regex in the parser
    int year = std::stoi(date.value.substr(0, 4));
    int month = std::stoi(date.value.substr(5, 2));
    int day = std::stoi(date.value.substr(8, 2));

    // should make cap dynamic, current year + x years
    if (year < 2000 || year > 2100) {
        std::ostringstream message;
        message
            << "Year in date literal must be within range "
            << std::to_string(DATE_LITERAL_MINIMUM_YEAR)
            << "-"
            << std::to_string(DATE_LITERAL_MAXIMUM_YEAR);

        errors.push_back({
            SemanticErrorCode::InvalidDate,
            message.str(),
            0, // todo
            0 // todo
        });
    }

    if (month < 1 || month > 12) {
        std::ostringstream message;
        message
            << "Month in date literal must be within range "
            << std::to_string(DATE_LITERAL_MINIMUM_MONTH)
            << "-"
            << std::to_string(DATE_LITERAL_MAXIMUM_MONTH);

        errors.push_back({
            SemanticErrorCode::InvalidDate,
            message.str(),
            0, // todo
            0 // todo
        });
    }

    if (day < 1 || day > DATE_LITERAL_MAXIMUM_DAY[month]) {
        std::ostringstream message;
        message
            << "Day in date literal must be within range 1"
            << "-"
            << std::to_string(DATE_LITERAL_MAXIMUM_DAY[month]);

        errors.push_back({
            SemanticErrorCode::InvalidDate,
            message.str(),
            0, // todo
            0 // todo
        });
    }
}

void SemanticAnalyzer::analyzeTag(const TagStatementNode& tag) {
    
}

void SemanticAnalyzer::analyzeAttendee(const AttendeeStatementNode& attendee) {
    
}