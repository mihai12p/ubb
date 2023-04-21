using mpp_proiect_csharp_vreauladudu.domain;
using mpp_proiect_csharp_vreauladudu.service;
using System;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu
{
    public class MotoClientController : IMotoObserver
    {
        public event EventHandler<MotoUserEvent> UpdateEvent;
        private readonly IMotoService Server;
        private User CurrentUser;

        public MotoClientController(IMotoService server)
        {
            this.Server = server;
            this.CurrentUser = null;
        }

        public void login(String username, String password)
        {
            User user = new User();
            user.Username = username;
            user.Password = password;
            this.Server.login(user, this);
            Console.WriteLine("Login succeeded...");
            this.CurrentUser = user;
            Console.WriteLine("Current user {0}", user);
        }

        public void logout()
        {
            Console.WriteLine("Controller logout");
            this.Server.logout(this.CurrentUser, this);
            this.CurrentUser = null;
        }

        public Dictionary<int, List<Motorcycle>> listRaces()
        {
            Console.WriteLine("List races");
            return this.Server.listRaces(this);
        }

        public IEnumerable<Motorcycle> listMotorcycles()
        {
            Console.WriteLine("List motorcycles");
            return this.Server.listMotorcycles(this);
        }

        public List<Motorcycle> listMotorcyclesByCapacity(int capacity)
        {
            Console.WriteLine("List motorcycles by capacity");
            return this.Server.listMotorcyclesByCapacity(capacity, this);
        }

        public List<Participant> findParticipantForRace(int motorcycleId)
        {
            Console.WriteLine("Find participant for race");
            return this.Server.findParticipantForRace(motorcycleId, this);
        }

        public List<Motorcycle> listMotorcyclesByBrand(String brand)
        {
            Console.WriteLine("List motorcycles by brand");
            return this.Server.listMotorcyclesByBrand(brand, this);
        }

        public Motorcycle findMotorcycleById(int motorcycleId)
        {
            Console.WriteLine("Find motorcycle");
            return this.Server.findMotorcycleById(motorcycleId, this);
        }

        public void addParticipant(String participantName, String motorcycleBrand, int motorcycleCapacity)
        {
            Console.WriteLine("Add participant");
            this.Server.addParticipant(participantName, motorcycleBrand, motorcycleCapacity, this);
        }

        protected virtual void OnUserEvent(MotoUserEvent userEvent)
        {
            if (this.UpdateEvent == null)
            {
                return;
            }

            this.UpdateEvent(this, userEvent);
            Console.WriteLine("Update Event called");
        }

        public void participantAdded(Participant participant)
        {
            Console.WriteLine("Participant added, update lists");
            MotoUserEvent userEvent = new MotoUserEvent(UserEvent.ParticipantAdded, participant);
            this.OnUserEvent(userEvent);
        }
    }
}