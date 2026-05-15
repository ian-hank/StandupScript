#pragma once

#include <string>
#include <memory>
#include <optional>
#include <vector>

struct StatementNode {
    virtual ~StatementNode() = default;
};

struct SectionStatementNode : StatementNode {
    std::string title;
    std::vector<std::unique_ptr<StatementNode>> statements;
};

struct DateStatementNode : StatementNode {
    std::string value;
};

struct TagStatementNode : StatementNode {
    std::string value;
};

struct AttendeeStatementNode : StatementNode {
    std::string name;
    std::optional<std::string> alias;
};

struct SummaryStatementNode : StatementNode {
    std::string value;
};

struct NoteStatementNode : StatementNode {
    std::string value;
};

struct DecisionStatementNode : StatementNode {
    std::string value;
};

struct TodoStatementNode : StatementNode {
    std::vector<std::string> attendees;
    std::string date;
    std::optional<std::string> priority;
    std::string note;
};

struct BlockerStatementNode : StatementNode {
    std::vector<std::string> attendees;
    std::string note;
};

struct RiskStatementNode : StatementNode {
    std::string value;
    std::optional<std::string> priority;
    std::string note;
};

struct LinkStatementNode : StatementNode {
    std::string link;
    std::optional<std::string> note;
};