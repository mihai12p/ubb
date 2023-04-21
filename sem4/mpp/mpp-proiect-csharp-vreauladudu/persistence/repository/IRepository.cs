using mpp_proiect_csharp_vreauladudu.domain;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu.repository
{
    public interface IRepository<ID, E> where E : Entity<ID>
    {
        E find(ID id);
        IEnumerable<E> findAll();
        E save(E e);
        E remove(ID id);
        E update(E e);
    }
}