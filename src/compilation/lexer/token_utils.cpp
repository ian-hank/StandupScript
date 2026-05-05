#include <iostream>
#include <iomanip>

#include "token_utils.h"
#include "tokens.h"

std::string TokenUtils::tokenTypeToString(const TokenType& type) {
    switch (type) {
        // Identifiers
        case TokenType::eof:                    return "eof";
        case TokenType::identifier:             return "identifier";

        // Literals
        case TokenType::lit_date:               return "lit_date";
        case TokenType::lit_string:             return "lit_string";
        //case TokenType::lit_time:               return "lit_time";

        // Keywords
        case TokenType::kw_as:                  return "kw_as";
        case TokenType::kw_attendee:            return "kw_attendee";
        case TokenType::kw_blocker:             return "kw_blocker";
        case TokenType::kw_by:                  return "kw_by";
        case TokenType::kw_date:                return "kw_date";
        case TokenType::kw_decision:            return "kw_decision";
        case TokenType::kw_high:                return "kw_high";
        case TokenType::kw_link:                return "kw_link";
        case TokenType::kw_low:                 return "kw_low";
        case TokenType::kw_medium:              return "kw_medium";
        case TokenType::kw_meeting:             return "kw_meeting";
        case TokenType::kw_note:                return "kw_note";
        case TokenType::kw_priority:            return "kw_priority";
        case TokenType::kw_risk:                return "kw_risk";
        case TokenType::kw_section:             return "kw_section";
        case TokenType::kw_standup:             return "kw_standup";
        case TokenType::kw_summary:             return "kw_summary";
        case TokenType::kw_tag:                 return "kw_tag";
        case TokenType::kw_time:                return "kw_time";
        case TokenType::kw_timezone:            return "kw_timezone";
        case TokenType::kw_todo:                return "kw_todo";

        // Separators 
        case TokenType::left_curly_bracket:     return "left_curly_bracket";
        case TokenType::right_curly_bracket:    return "right_curly_bracket";
        case TokenType::left_parenthese:        return "left_parenthese";
        case TokenType::right_parentheses:      return "right_parentheses";
        case TokenType::comma:                  return "comma";
        case TokenType::colon:                  return "colon";
        case TokenType::semicolon:              return "semicolon";
        case TokenType::at:                     return "at";

        default:                                return "token_not_included_in_tokenutils";
    }
}

void TokenUtils::printTokens(const std::vector<Token>& tokens) {
    std::cout << "================ TOKENS =================\n";
    for (int i = 0; i < static_cast<int>(tokens.size()); i++) {
        std::cout 
            << '[' << std::setw(3) << std::setfill('0') << i + 1 << "] "
            << std::left << std::setfill(' ')
            << std::setw(14) << tokenTypeToString(tokens[i].tokenType)
            << " @ " << tokens[i].line << ':' << tokens[i].column << " "
            << "\"" << tokens[i].value.value_or("null")  << "\""
            << '\n';
    }
}