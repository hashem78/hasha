//
// Created by mythi on 26/08/22.
//

#ifndef HASHA_ELSESTATEMENT_H
#define HASHA_ELSESTATEMENT_H

#include "Token.h"
#include "Block.h"

namespace hasha {

    class ElseStatement : public Token {
        Block::Ptr m_block;
    public:
        using Ptr = std::unique_ptr<ElseStatement>;

        ElseStatement(
                Block::Ptr block,
                const Span &span,
                int scope_id
        );

        static ElseStatement::Ptr create(
                Block::Ptr block,
                const Span &span,
                int scope_id
        );


        [[nodiscard]]
        nlohmann::json to_json() const override;

        [[nodiscard]]
        const Block &block() const;
    };

} // hasha

#endif //HASHA_ELSESTATEMENT_H
