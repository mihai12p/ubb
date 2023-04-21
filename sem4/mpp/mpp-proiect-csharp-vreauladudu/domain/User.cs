using System;

namespace mpp_proiect_csharp_vreauladudu.domain
{
    [Serializable]
    public class User : Entity<int>
    {
        public String Username { get; set; }
        public String Password { get; set; }
    }
}