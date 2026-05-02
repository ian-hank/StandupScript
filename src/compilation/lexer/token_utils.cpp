#include <iostream>

#include "token_utils.h"
#include "tokens.h"

std::string  TokenUtils::tokenTypeToString(TokenType type) {
    switch (type) {
        // Keywords
        case TokenType::kw_as:              return "kw_as";
        case TokenType::kw_attendee:        return "kw_attendee";
        case TokenType::kw_date:            return "kw_date";
        case TokenType::kw_note:            return "kw_note";
        case TokenType::kw_standup:         return "kw_standup";
        case TokenType::kw_summary:         return "kw_summary";
        case TokenType::kw_tag:             return "kw_tag";

        default:                            return "token_not_included_in_tokenutils";
    }
}

void TokenUtils::printTokens(std::vector<Token>& tokens) {
    std::cout << "================ TOKENS =================\n";
    for (int i = 0; i < static_cast<int>(tokens.size()); i++) {
        std::cout << "[" << i + 1 << "] Type: " << tokenTypeToString(tokens[i].tokenType) << std::endl;
    }
}