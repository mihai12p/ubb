#pragma once

#include "ADatabase.hpp"
#include "UserRepository.hpp"

class UserDatabase : public UserRepository
{
public:
    UserDatabase() : UserRepository("Users") { }

protected:
    qx_query findStatement(qint32 id) override;

public:
    qint32 isValidUser(const QString& username, const QString& password) override;
};