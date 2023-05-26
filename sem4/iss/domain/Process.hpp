#pragma once

#include "Entity.hpp"

class QX_DLL_EXPORT_HELPER Process : public Entity<qint32>
{
public:
    Process() : Entity(0) { };

    Process(qint32 PID, qint32 PPID, const QString& name) : Entity(0), PID{ PID }, ParentPID{ PPID }, name(name) { }
    Process(qint32 id, qint32 PID, qint32 PPID, const QString& name) : Entity(id), PID{ PID }, ParentPID{ PPID }, name(name) { }

    const qint32 getPID() const
    {
        return this->PID;
    }

    void setPID(qint32 PID)
    {
        this->PID = PID;
    }

    const qint32 getPPID() const
    {
        return this->ParentPID;
    }

    void setPPID(qint32 PPID)
    {
        this->ParentPID = PPID;
    }

    const QString& getName() const
    {
        return this->name;
    }

    void setName(const QString& name)
    {
        this->name = name;
    }

    const qint32 getAction() const
    {
        return this->action;
    }

    void setAction(qint32 action)
    {
        this->action = action;
    }

    const QList<QString> getDetails();

public:
    qint32 PID = 0;
    qint32 ParentPID = 0;
    QString name{ };
    qint32 action = 0;
};

QX_REGISTER_PRIMARY_KEY(Process, qint32)
QX_REGISTER_HPP_EXPORT_DLL(Process, qx::trait::no_base_class_defined, 1)