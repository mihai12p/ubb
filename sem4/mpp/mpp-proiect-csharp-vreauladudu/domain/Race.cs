namespace mpp_proiect_csharp_vreauladudu.domain
{
    enum MotorcycleCategory
    {
        SLOW_125CMC,
        AVERAGE_250CMC,
        FAST_600CMC,
        SUPERFAST_1000CMC,

        MAX_CAPACITY
    }

    internal class Race : Entity<int>
    {
        public MotorcycleCategory motorcycleCategory { get; set; }
        public List<Participant>? participants { get; set; }
    }
}