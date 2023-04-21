using mpp_proiect_csharp_vreauladudu.domain;
using System;

namespace mpp_proiect_csharp_vreauladudu.repository
{
    public interface UserRepository : IRepository<int, User>
    {
        User isValidUser(String username, String password);
    }
}