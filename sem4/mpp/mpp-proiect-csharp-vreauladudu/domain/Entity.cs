using System;

namespace mpp_proiect_csharp_vreauladudu.domain
{
    [Serializable]
    public class Entity<ID>
    {
        public ID Id { get; set; }
    }
}