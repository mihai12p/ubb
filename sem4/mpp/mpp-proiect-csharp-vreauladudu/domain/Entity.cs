using Newtonsoft.Json;
using System;

namespace mpp_proiect_csharp_vreauladudu.domain
{
    [Serializable]
    public class Entity<ID>
    {
        [JsonProperty("id")]
        public ID Id { get; set; }
    }
}