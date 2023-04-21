using mpp_proiect_csharp_vreauladudu.domain;
using System;

namespace networking
{
    public interface Request { }

    [Serializable]
    public class LoginRequest : Request
    {
        private User user;

        public LoginRequest(User user)
        {
            this.user = user;
        }

        public virtual User User { get { return this.user; } }
    }

    [Serializable]
    public class LogoutRequest : Request
    {
        private User user;
        
        public LogoutRequest(User user)
        {
            this.user = user;
        }

        public virtual User User { get { return this.user; } }
    }

    [Serializable]
    public class ListRacesRequest : Request { }
    
    [Serializable]
    public class ListMotorcyclesRequest : Request { }
    
    [Serializable]
    public class ListMotorcyclesByCapacityRequest : Request
    {
        private int capacity;

        public ListMotorcyclesByCapacityRequest(int capacity)
        {
            this.capacity = capacity;
        }

        public virtual int Capacity { get { return this.capacity; } }
    }
    
    [Serializable]
    public class FindParticipantsRequest : Request
    {
        private int motorcycleId;

        public FindParticipantsRequest(int motorcycleId)
        {
            this.motorcycleId = motorcycleId;
        }

        public virtual int MotorcycleId { get { return this.motorcycleId; } }
    }

    [Serializable]
    public class ListMotorcyclesByBrandRequest : Request
    {
        private String brand;

        public ListMotorcyclesByBrandRequest(String brand)
        {
            this.brand = brand;
        }

        public virtual String Brand { get { return this.brand; } }
    }

    [Serializable]
    public class FindMotorcycleRequest : Request
    {
        private int motorcycleId;

        public FindMotorcycleRequest(int motorcycleId)
        {
            this.motorcycleId = motorcycleId;
        }

        public virtual int MotorcycleId { get { return this.motorcycleId; } }
    }
    
    [Serializable]
    public class AddParticipantRequest : Request
    {
        private String participantName;
        private String motorcycleBrand;
        private int motorcycleCapacity;

        public AddParticipantRequest(String participantName, String motorcycleBrand, int motorcycleCapacity)
        {
            this.participantName = participantName;
            this.motorcycleBrand = motorcycleBrand;
            this.motorcycleCapacity = motorcycleCapacity;
        }

        public virtual String ParticipantName { get { return this.participantName; } }
        public virtual String MotorcycleBrand { get { return this.motorcycleBrand; } }
        public virtual int MotorcycleCapacity { get { return this.motorcycleCapacity; } }
    }
}