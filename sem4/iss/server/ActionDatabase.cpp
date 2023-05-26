#include "ActionDatabase.hpp"

qx_query ActionDatabase::findStatement(qint32 id)
{
    qx_query query("SELECT * FROM Process WHERE id = :id");
    query.bind(":id", id);
    return query;
}