//
// Created by mythi on 03/09/22.
//

#ifndef HASHA_ANALYZER_H
#define HASHA_ANALYZER_H


#include "ErrorOr.h"
#include "Lexeme.h"

namespace hasha {

    class Analyzer {
        const LexemeList &lexemes;
    public:
        explicit Analyzer(const LexemeList &lexemes);

        ErrorOr<void> analyze_bracket_pairs();
    };

} // hasha

#endif //HASHA_ANALYZER_H
