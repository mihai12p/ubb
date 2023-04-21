using mpp_proiect_csharp_vreauladudu.domain;
using System;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu.repository
{
    public interface MotorcycleRepository : IRepository<int, Motorcycle>
    {
        List<Motorcycle> findByCapacity(int Capacity);
        List<Motorcycle> findByBrand(String Brand);
        Motorcycle findById(int Id);
    }
}