#pragma once

#include "ADatabase.hpp"
#include "ActionRepository.hpp"

class ActionDatabase : public ActionRepository
{
public:
    ActionDatabase() : ActionRepository("Process") { }

protected:
    qx_query findStatement(qint32 id) override;
};