#pragma once

#include <string>
#include <vector>

enum class TokenType {
    // Identifiers
    eof,                    // end of file
    identifier,

    // Literals
    lit_string,             // 'c' or 'cat'
    lit_date,               // 'YYYY-MM-DD'
    //lit_time,

    // Separators
    left_curly_bracket,     // '{'
    right_curly_bracket,    // '}'
    left_parenthese,        // '()'
    right_parentheses,      // ')'
    comma,                  // ','
    colon,                  // ':'
    semicolon,              // ';'
    at,                     // '@'

    // Keywords (reserved)
    kw_standup,             // 'standup'
    kw_meeting,             // 'meeting'
    kw_date,                // 'date'
    kw_time,                // 'time'
    kw_timezone,            // 'timezone
    kw_tag,                 // 'tag'
    kw_attendee,            // 'attendee'
    kw_as,                  // 'as'
    kw_summary,             // 'summary'
    kw_note,                // 'note'
    };

struct Token {
    TokenType tokenType;
    std::optional<std::string> value;
    int line;
    int column;
};