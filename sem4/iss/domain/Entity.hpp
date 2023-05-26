#pragma once

#include <QxOrm.h>

template <typename T>
class Entity
{
public:
    Entity(T id) : id(id) { }

    const T getId() const
    {
        return this->id;
    }

    void setId(T id)
    {
        this->id = id;
    }

public:
    T id = 0;
};