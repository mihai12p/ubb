#include "User.hpp"
#include <QxMemLeak.h>

QX_REGISTER_CPP_EXPORT_DLL(User)

namespace qx
{
template <>
void register_class(QxClass<User>& t)
{
    t.id(&User::id, "uid");
    t.data(&User::username, "username");
    t.data(&User::password, "password");
    t.data(&User::license, "license");
    t.data(&User::isAdministrator, "isAdministrator");
}}