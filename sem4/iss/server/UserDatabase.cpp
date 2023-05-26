#include "UserDatabase.hpp"

qx_query UserDatabase::findStatement(qint32 id)
{
    qx_query query("SELECT * FROM Users WHERE uid = :uid");
    query.bind(":uid", id);
    return query;
}

qint32 UserDatabase::isValidUser(const QString& username, const QString& password)
{
    qx_query query("SELECT * FROM Users WHERE username = :username AND password = :password");
    query.bind(":username", username);
    query.bind(":password", password);

    QList<User> result{ };
    QSqlError daoError = qx::dao::execute_query(query, result);
    return (result.size() == 1) ? result.at(0).getId() : 0;
}