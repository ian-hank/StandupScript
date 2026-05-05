#pragma once

#include <string>
#include <vector>


enum class TokenType {
    // Identifiers
    eof,                    // end of file
    identifier,

    // Literals
    lit_date,               // 'YYYY-MM-DD'
    lit_string,             // 'c' or 'cat'
    //lit_time,

    // Separators
    at,                     // '@'
    colon,                  // ':'
    comma,                  // ','
    left_curly_bracket,     // '{'
    right_curly_bracket,    // '}'
    left_parenthese,        // '('
    right_parentheses,      // ')'
    semicolon,              // ';'

    // Keywords (reserved)
    kw_as,                  // 'as'
    kw_attendee,            // 'attendee'
    kw_blocker,             // 'blocker'
    kw_by,                  // 'by'
    kw_date,                // 'date'
    kw_decision,            // 'decision'
    kw_high,                // 'high'
    kw_link,                // 'link'
    kw_low,                 // 'low'
    kw_medium,              // 'medium'
    kw_meeting,             // 'meeting'
    kw_note,                // 'note'
    kw_priority,            // 'priority'
    kw_risk,                // 'risk'
    kw_section,             // 'section'
    kw_standup,             // 'standup'
    kw_summary,             // 'summary'
    kw_tag,                 // 'tag'
    kw_time,                // 'time'
    kw_timezone,            // 'timezone
    kw_todo,                // 'todo'
};

struct Token {
    TokenType tokenType;
    std::optional<std::string> value;
    int line;
    int column;
};