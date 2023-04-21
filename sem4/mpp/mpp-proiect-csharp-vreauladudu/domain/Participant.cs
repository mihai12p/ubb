using System;

namespace mpp_proiect_csharp_vreauladudu.domain
{
    [Serializable]
    public class Participant : Entity<int>
    {
        public String Name { get; set; }
        public int MotorcycleID { get; set; }

        public override string ToString()
        {
            return "ID: " + this.Id + " | Name: " + this.Name + " | MotorcycleId: " + this.MotorcycleID;
        }
    }
}