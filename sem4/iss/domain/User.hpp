#pragma once

#include "Entity.hpp"
#include <QtCore/qstring.h>
#include <QtCore/qdatastream.h>

class QX_DLL_EXPORT_HELPER User : public Entity<qint32>
{
public:
    User() : Entity(0) { };
    virtual ~User() { }

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
    
    const QString& getLicense() const
    {
        return this->license;
    }

    void setLicense(const QString& license)
    {
        this->license = license;
    }

    virtual bool IsAdministrator()
    {
        return this->isAdministrator;
    }

public:
    QString username{ };
    QString password{ };
    QString license{ };
    bool    isAdministrator = false;
};

QX_REGISTER_PRIMARY_KEY(User, qint32)
QX_REGISTER_HPP_EXPORT_DLL(User, qx::trait::no_base_class_defined, 1)

class Administrator : public User
{
public:
    Administrator(const QString& username, const QString& password) : User(username, password)
    {
        this->isAdministrator = true;
    }

    Administrator(qint32 id, const QString& username, const QString& password) : User(id, username, password)
    {
        this->isAdministrator = true;
    }

    bool IsAdministrator() override
    {
        return true;
    }
};