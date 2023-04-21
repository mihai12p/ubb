using mpp_proiect_csharp_vreauladudu.domain;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu.repository
{
    public interface ParticipantRepository : IRepository<int, Participant>
    {
        List<Participant> findByMotorcycleId(int MotorcycleId);
    }
}