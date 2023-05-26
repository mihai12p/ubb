#pragma once

#include <qlist.h>
#include "IRepository.hpp"
#include "../domain/Entity.hpp"

template <typename ID, typename E>
class ADatabase : public IRepository<ID, E>
{
    static_assert(std::is_base_of<Entity<ID>, E>::value, "E must derive from Entity");

public:
    explicit ADatabase(const QString& tableName)
    {
        this->tableName = tableName;
    }

    virtual ~ADatabase() { }

protected:
    virtual qx_query findStatement(ID id) = 0;

public:
    E find(ID id) override
    {
        if (!id)
        {
            throw std::exception("id must not be null");
        }

        QList<E> result{ };
        QSqlError daoError = qx::dao::fetch_by_query(this->findStatement(id), result);
        if (result.size() == 1)
        {
            return result.at(0);
        }

        return E();
    }

    QList<E> findAll() override
    {
        QList<E> entities{ };

        qx_query query("SELECT * FROM " + this->tableName);

        QList<E> result{ };
        QSqlError daoError = qx::dao::execute_query(query, result);
        if (result.size() > 0)
        {
            for (const E& entity : result)
            {
                entities.append(entity);
            }
        }

        return entities;
    }

    E save(E entity) override
    {
        QSqlError daoError = qx::dao::save(entity);
        return entity;
    }

    E remove(ID id) override
    {
        if (!id)
        {
            throw std::exception("id must not be null");
        }

        E entity = this->find(id);
        if (entity.getId())
        {
            QSqlError daoError = qx::dao::delete_by_id(entity);
        }

        return entity;
    }

    E update(E entity) override
    {
        QSqlError daoError = qx::dao::update(entity);
        return entity;
    }

private:
    QString tableName{ };
};