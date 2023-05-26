#pragma once

#include "ADatabase.hpp"
#include "../domain/User.hpp"

class UserRepository : public ADatabase<qint32, User>
{
public:
    explicit UserRepository(const QString& tableName) : ADatabase(tableName) { }
    virtual ~UserRepository() { }

    virtual qint32 isValidUser(const QString& username, const QString& password) = 0;
};