#pragma once

#include "Entity.hpp"
#include <QtCore/qstring.h>
#include <QtCore/qdatastream.h>

class User : public Entity<qint32>
{
public:
    User() : Entity(0) { };
    User(const QString& username, const QString& password) : Entity(0), username(username), password(password) { }
    User(qint32 id, const QString& username, const QString& password) : Entity(id), username(username), password(password) { }

    const QString& getUsername() const
    {
        return this->username;
    }

    void setUsername(const QString& username)
    {
        this->username = username;
    }

    const QString& getPassword() const
    {
        return this->password;
    }

    void setPassword(const QString& password)
    {
        this->password = password;
    }

    friend QDataStream& operator<<(QDataStream& dataStream, const User& user)
    {
        dataStream << user.getId() << user.getUsername() << user.getPassword();
        return dataStream;
    }

    friend QDataStream& operator>>(QDataStream& dataStream, User& user)
    {
        qint32 id;
        QString username{ };
        QString password{ };
        dataStream >> id >> username >> password;
        user.setId(id);
        user.setUsername(username);
        user.setPassword(password);
        return dataStream;
    }

private:
    QString username{ };
    QString password{ };
};