#pragma once

#include <unordered_map>

#include "tokens.h"

namespace LexerConstants {
    const std::unordered_map<std::string, TokenType> keywords = {
        { "as",         TokenType::kw_as },
        { "attendee",   TokenType::kw_attendee },
        { "blocker",    TokenType::kw_blocker },
        { "by",         TokenType::kw_by },
        { "date",       TokenType::kw_date },
        { "decision",   TokenType::kw_decision},
        { "high",       TokenType::kw_priority_high},
        { "link",       TokenType::kw_link},
        { "low",        TokenType::kw_priority_low},
        { "medium",     TokenType::kw_priority_medium},
        { "meeting",    TokenType::kw_meeting},
        { "note",       TokenType::kw_note },
        { "priority",   TokenType::kw_priority },
        { "risk",       TokenType::kw_risk },
        { "section",    TokenType::kw_section },
        { "standup",    TokenType::kw_standup },
        { "summary",    TokenType::kw_summary },
        { "tag",        TokenType::kw_tag },
        { "time",       TokenType::kw_time },
        { "timezone",   TokenType::kw_timezone},
        { "todo",       TokenType::kw_todo },
    };

    const std::unordered_map<char, TokenType> separators = {
        { '{', TokenType::left_curly_bracket },
        { '}', TokenType::right_curly_bracket },
        { '(', TokenType::left_parenthese },
        { ')', TokenType::right_parentheses },
        { ',', TokenType::comma },
        { ':', TokenType::colon },
        { ';', TokenType::semicolon },
        { '@', TokenType::at },
    };
}