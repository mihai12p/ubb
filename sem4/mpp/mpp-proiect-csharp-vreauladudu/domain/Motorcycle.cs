using System;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu.domain
{
    [Serializable]
    public class Motorcycle : Entity<int>
    {
        public String Brand { get; set; }
        public int Capacity { get; set; }

        public override bool Equals(object obj)
        {
            return obj is Motorcycle motorcycle &&
                   this.Id == motorcycle.Id;
        }

        public override int GetHashCode()
        {
            int hashCode = -237277777;
            hashCode = hashCode * -1521134295 + this.Id.GetHashCode();
            hashCode = hashCode * -1521134295 + EqualityComparer<string>.Default.GetHashCode(this.Brand);
            hashCode = hashCode * -1521134295 + this.Capacity.GetHashCode();
            return hashCode;
        }

        public override string ToString()
        {
            return "ID: " + this.Id + " | Brand: " + this.Brand + " | Capacitate: " + this.Capacity;
        }
    }
}