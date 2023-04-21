using mpp_proiect_csharp_vreauladudu.domain;
using System;
using System.Collections.Generic;

namespace networking
{
    public interface Response { }

    [Serializable]
    public class OkResponse : Response { }

    [Serializable]
    public class ErrorResponse : Response
    {
        private string message;

        public ErrorResponse(string message)
        {
            this.message = message;
        }

        public virtual string Message { get { return this.message; } }
    }

    [Serializable]
    public class ListRacesResponse : Response
    {
        private Dictionary<int, List<Motorcycle>> races;

        public ListRacesResponse(Dictionary<int, List<Motorcycle>> races)
        {
            this.races = races;
        }

        public virtual Dictionary<int, List<Motorcycle>> Races { get { return this.races; } }
    }
    
    [Serializable]
    public class ListMotorcyclesResponse : Response
    {
        private IEnumerable<Motorcycle> motorcycles;
        private List<Motorcycle> motorcyclesList;

        public ListMotorcyclesResponse(IEnumerable<Motorcycle> motorcycles)
        {
            this.motorcycles = motorcycles;
        }

        public ListMotorcyclesResponse(List<Motorcycle> motorcycles)
        {
            this.motorcyclesList = motorcycles;
        }

        public virtual IEnumerable<Motorcycle> Motorcycles { get { return this.motorcycles; } }

        public virtual List<Motorcycle> MotorcyclesList { get { return this.motorcyclesList; } }
    }
    
    [Serializable]
    public class FindParticipantsResponse : Response
    {
        private List<Participant> participantsForRace;

        public FindParticipantsResponse(List<Participant> participants)
        {
            this.participantsForRace = participants;
        }

        public virtual List<Participant> Participants { get { return this.participantsForRace; } }
    }

    [Serializable]
    public class MotorcycleResponse : Response
    {
        private Motorcycle motorcycle;

        public MotorcycleResponse(Motorcycle motorcycle)
        {
            this.motorcycle = motorcycle;
        }

        public virtual Motorcycle Motorcycle { get { return this.motorcycle; } }
    }

    [Serializable]
    public class ParticipantResponse : Response { }

    public interface UpdateResponse : Response { }

    [Serializable]
    public class ParticipantAddedResponse : UpdateResponse
    {
        private Participant participant;

        public ParticipantAddedResponse(Participant participant)
        {
            this.participant = participant;
        }

        public virtual Participant Participant { get {  return this.participant; } }
    }
}