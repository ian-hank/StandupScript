# StandupScript Language Specification

**Status:** Draft
**Last updated:** 2028-04-28
**Language name:** StandupScript  
**Canonical file extension:** `.stup`  
**Supported file extension aliases:** `.standup`  
**Compiler executable:** `standupc`  
**Primary purpose:** Compile structured standups and meeting notes into Markdown summaries, JSON data, follow-up emails, task exports, calendar/task artifacts, and optional visualizations.

## 1. Tokens

StandupScript compiler should recognize at least the following token kinds.
Semicolons are optional and should be accepted but NOT required.

```txt
EOF

Identifier
StringLiteral
DateLiteral
TimeLiteral

LeftBrace       {
RightBrace      }
LeftParen       (
RightParen      )
Comma           ,
Colon           :
Semicolon       ;
At              @

KeywordStandup
KeywordMeeting
KeywordDate
KeywordTime
KeywordTimezone
KeywordTag
KeywordAttendee
KeywordAs
KeywordSummary
KeywordNote
```