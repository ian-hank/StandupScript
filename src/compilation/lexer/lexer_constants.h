#pragma once

#include <unordered_map>

#include "tokens.h"

namespace LexerConstants {
    const std::unordered_map<std::string, TokenType> keywords = {
        { "as", TokenType::kw_as },
        { "attendee", TokenType::kw_attendee },
        { "date", TokenType::kw_date },
        { "note", TokenType::kw_note },
        { "standup", TokenType::kw_standup },
        { "summary", TokenType::kw_summary },
        { "tag", TokenType::kw_tag },
    };
}