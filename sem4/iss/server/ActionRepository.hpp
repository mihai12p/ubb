#pragma once

#include "ADatabase.hpp"
#include "../domain/Process.hpp"

class ActionRepository : public ADatabase<qint32, Process>
{
public:
    explicit ActionRepository(const QString& tableName) : ADatabase(tableName) { }
};