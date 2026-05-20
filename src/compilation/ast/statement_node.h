#pragma once

#include <string>
#include <memory>
#include <optional>
#include <vector>

#include "source_location.h"

struct StatementNode {
    virtual ~StatementNode() = default;
};

struct SectionStatementNode : StatementNode {
    std::string title;
    std::vector<std::unique_ptr<StatementNode>> statements;
    SourceSpan location;
};

struct DateStatementNode : StatementNode {
    std::string value;
    SourceSpan location;
};

struct TagStatementNode : StatementNode {
    std::string value;
    SourceSpan location;
};

struct AttendeeStatementNode : StatementNode {
    std::string attendee;
    std::optional<std::string> alias;
    SourceSpan location;
};

struct SummaryStatementNode : StatementNode {
    std::string value;
    SourceSpan location;
};

struct NoteStatementNode : StatementNode {
    std::string value;
    SourceSpan location;
};

struct DecisionStatementNode : StatementNode {
    std::string value;
    SourceSpan location;
};

struct TodoStatementNode : StatementNode {
    std::vector<std::string> attendees;
    std::optional<std::string> date;
    std::optional<std::string> priority;
    std::string note;
    SourceSpan location;
};

struct BlockerStatementNode : StatementNode {
    std::vector<std::string> attendees;
    std::string note;
    SourceSpan location;
};

struct RiskStatementNode : StatementNode {
    std::optional<std::string> priority;
    std::string note;
    SourceSpan location;
};

struct LinkStatementNode : StatementNode {
    std::string link;
    std::optional<std::string> note;
    SourceSpan location;
};