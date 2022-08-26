//
// Created by mythi on 26/08/22.
//

#ifndef HASHA_IFSTATEMENT_H
#define HASHA_IFSTATEMENT_H

#include "Token.h"
#include "Block.h"

namespace hasha {

    class IfStatement : public Token {
    protected:
        TokenListPtr condition;
        Block::Ptr block;
    public:
        using Ptr = std::unique_ptr<IfStatement>;

        IfStatement(TokenListPtr condition, Block::Ptr block);

        static Ptr create(TokenListPtr condition, Block::Ptr block);

        [[nodiscard]]
        const TokenList * get_condition() const;

        [[nodiscard]]
        const Block * get_block() const;

        [[nodiscard]]
        nlohmann::json to_json() const override;

    };



} // hasha

#endif //HASHA_IFSTATEMENT_H
