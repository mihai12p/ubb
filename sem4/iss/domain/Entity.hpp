#pragma once

template <class T>
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

private:
    T id = 0;
};