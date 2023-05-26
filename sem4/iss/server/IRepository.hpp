#pragma once

#include <qlist.h>
#include "../domain/Entity.hpp"

template <typename ID, typename E>
class IRepository
{
    static_assert(std::is_base_of<Entity<ID>, E>::value, "E must derive from Entity");

public:
    virtual ~IRepository() { }

    virtual E find(ID id) = 0;
    virtual QList<E> findAll() = 0;
    virtual E save(E entity) = 0;
    virtual E remove(ID id) = 0;
    virtual E update(E entity) = 0;
};