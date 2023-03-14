using mpp_proiect_csharp_vreauladudu.domain;
using mpp_proiect_csharp_vreauladudu.repository;

namespace mpp_proiect_csharp_vreauladudu.service
{
    internal class Service
    {
        private IRepository<int, Motorcycle> motorcycles;
        private IRepository<int, Participant> participants;
        private IRepository<int, Team> teams;
        private IRepository<int, Race> races;
    
        public Service()
        {

        }
    }
}