namespace mpp_proiect_csharp_vreauladudu.domain
{
    internal class Participant : Entity<int>
    {
        public String? name { get; set; }
        public Motorcycle? motorcycle { get; set; }
        public Team? team { get; set; }
    }
}