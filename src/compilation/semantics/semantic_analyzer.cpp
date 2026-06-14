#include <sstream>

#include "semantic_analyzer.h"

std::vector<SemanticError> SemanticAnalyzer::getErrors() {
    return errors;
}

SourceSpan SemanticAnalyzer::getSourceSpan(const StatementNode& node) {
    SourceSpan nodeSource;
    nodeSource.start.line = node.location.start.line;
    nodeSource.start.column = node.location.start.column;
    nodeSource.end.line = node.location.end.line;
    nodeSource.end.column = node.location.end.column;

    return nodeSource;
}

void addError(std::vector<SemanticError>& errors, std::string errorMessage, SemanticErrorCode errorCode, SourceSpan source) {
    errors.push_back({
        errorCode,
        errorMessage,
        source
    });
}

bool SemanticAnalyzer::analyzeProgram() {
    analyzeStandup(*program.standup);

    return errors.empty();
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
    } else if (const auto* tagStatement = dynamic_cast<const TagStatementNode*>(&statement)) {
        analyzeTag(*tagStatement);
    } else if (const auto* attendeeStatement = dynamic_cast<const AttendeeStatementNode*>(&statement)) {
        analyzeAttendee(*attendeeStatement);
    } else if (const auto *summaryStatement = dynamic_cast<const SummaryStatementNode*>(&statement)) {
        analyzeSummary(*summaryStatement);
    }
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
            SemanticErrorCode::InvalidDate_YearRange,
            message.str(),
            getSourceSpan(date)
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
            SemanticErrorCode::InvalidDate_MonthRange,
            message.str(),
            getSourceSpan(date)
        });
    }

    if (day < 1 || day > DATE_LITERAL_MAXIMUM_DAY[month]) {
        std::ostringstream message;
        message
            << "Day in date literal must be within range 1"
            << "-"
            << std::to_string(DATE_LITERAL_MAXIMUM_DAY[month]);

        errors.push_back({
            SemanticErrorCode::InvalidDate_DayRange,
            message.str(),
            getSourceSpan(date)
        });
    }
}

void SemanticAnalyzer::analyzeTag(const TagStatementNode& tag) {
    if (tags.count(tag.value)) {
        std::ostringstream message;
        message
            << "Tag has already been defined, you can not duplicate tag->"
            << tag.value;

        errors.push_back({
            SemanticErrorCode::TagDeclared,
            message.str(),
            getSourceSpan(tag)
        });
    }

    tags.insert(tag.value);
}

void SemanticAnalyzer::analyzeAttendee(const AttendeeStatementNode& attendee) {
    if (attendeesByName.count(attendee.attendee)) {
        std::ostringstream message;
        message
            << "Attendee has already been defined, you can not duplicate attendee->"
            << attendee.attendee;

        errors.push_back({
            SemanticErrorCode::AttendeeDeclared,
            message.str(),
            getSourceSpan(attendee)
        });
    }

    if (attendee.alias.has_value()) {
        if (attendeesByAlias.count(attendee.alias.value())) {
            std::ostringstream message;
            message
                << "Attendee alias has already been defined, you can not duplicate alias->"
                << attendee.alias.value();

            errors.push_back({
                SemanticErrorCode::AttendeeAliasDeclared,
                message.str(),
                getSourceSpan(attendee)
            });
        }

        if (attendeesByName.count(attendee.alias.value())) {
            std::ostringstream message;
            message
                << "Attendee alias has already been defined, you can not duplicate alias->"
                << attendee.alias.value();

            errors.push_back({
                SemanticErrorCode::AttendeeAliasDeclared,
                message.str(),
                getSourceSpan(attendee)
            });
        }
    }

    int id = attendees.size();
    attendees.push_back({
        .id = id,
        .name = attendee.attendee,
        .alias = attendee.alias,
        .location = attendee.location
    });

    attendeesByName[attendee.attendee] = id;
    if (attendee.alias.has_value()) {
        attendeesByAlias[attendee.alias.value()] = id;
    }
 }

 void SemanticAnalyzer::analyzeSummary(const SummaryStatementNode& summary) {

 }
