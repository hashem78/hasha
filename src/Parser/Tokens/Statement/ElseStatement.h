//
// Created by mythi on 26/08/22.
//

#ifndef HASHA_ELSESTATEMENT_H
#define HASHA_ELSESTATEMENT_H

#include "IfStatement.h"

namespace hasha {

    class ElseStatement : public IfStatement {

    public:
        ElseStatement(Block::Ptr block);

        using Ptr = std::unique_ptr<ElseStatement>;

        static ElseStatement::Ptr create(Block::Ptr block);

        [[nodiscard]]
        nlohmann::json to_json() const override;
    };

} // hasha

#endif //HASHA_ELSESTATEMENT_H