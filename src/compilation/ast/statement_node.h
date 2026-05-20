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
    SourceLocation location;
};

struct DateStatementNode : StatementNode {
    std::string value;
    SourceLocation location;
};

struct TagStatementNode : StatementNode {
    std::string value;
    SourceLocation location;
};

struct AttendeeStatementNode : StatementNode {
    std::string attendee;
    std::optional<std::string> alias;
    SourceLocation location;
};

struct SummaryStatementNode : StatementNode {
    std::string value;
    SourceLocation location;
};

struct NoteStatementNode : StatementNode {
    std::string value;
    SourceLocation location;
};

struct DecisionStatementNode : StatementNode {
    std::string value;
    SourceLocation location;
};

struct TodoStatementNode : StatementNode {
    std::vector<std::string> attendees;
    std::optional<std::string> date;
    std::optional<std::string> priority;
    std::string note;
    SourceLocation location;
};

struct BlockerStatementNode : StatementNode {
    std::vector<std::string> attendees;
    std::string note;
    SourceLocation location;
};

struct RiskStatementNode : StatementNode {
    std::optional<std::string> priority;
    std::string note;
    SourceLocation location;
};

struct LinkStatementNode : StatementNode {
    std::string link;
    std::optional<std::string> note;
    SourceLocation location;
};