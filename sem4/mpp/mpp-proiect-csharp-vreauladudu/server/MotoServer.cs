using mpp_proiect_csharp_vreauladudu.repository;
using mpp_proiect_csharp_vreauladudu.service;
using mpp_proiect_csharp_vreauladudu.domain;
using System.Data.SQLite;
using services;

namespace Server.Impl
{
    public class MotoServer : IMotoService
    {
        private MotorcycleRepository motorcycles;
        private ParticipantRepository participants;
        private UserRepository users;
        private readonly IDictionary<int, IMotoObserver> loggedClients;

        public MotoServer(MotorcycleRepository motorcycles, ParticipantRepository participants, UserRepository users)
        {
            this.motorcycles = motorcycles;
            this.participants = participants;
            this.users = users;
            this.loggedClients = new Dictionary<int, IMotoObserver>();
        }

        public void login(User user, IMotoObserver client)
        {
            try
            {
                User userToLogIn = this.users.isValidUser(user.Username, user.Password);
                if (userToLogIn == null)
                {
                    throw new MotoException("Authentication failed.");
                }

                if (this.loggedClients.ContainsKey(userToLogIn.Id))
                {
                    throw new MotoException("User already logged in.");
                }

                this.loggedClients[userToLogIn.Id] = client;
            }
            catch (SQLiteException exception)
            {
                Console.Write(exception.StackTrace);
            }
        }

        public void logout(User user, IMotoObserver client)
        {
            try
            {
                User userToLogOut = this.users.isValidUser(user.Username, user.Password);
                if (userToLogOut == null)
                {
                    throw new MotoException("Unexpected error.");
                }

                if (!this.loggedClients.ContainsKey(userToLogOut.Id))
                {
                    throw new MotoException("User " + user + " is not logged in.");
                }

                this.loggedClients.Remove(userToLogOut.Id);
            }
            catch (SQLiteException exception)
            {
                Console.Write(exception.StackTrace);
            }
        }

        public Dictionary<int, List<Motorcycle>> listRaces(IMotoObserver client)
        {
            IEnumerable<Motorcycle> motorcycles = this.motorcycles.findAll();
            return motorcycles.GroupBy(motorcycle => motorcycle.Capacity).ToDictionary(motorcycle => motorcycle.Key, motorcycle => motorcycle.Select(r => r).ToList());
        }

        public IEnumerable<Motorcycle> listMotorcycles(IMotoObserver client)
        {
            return this.motorcycles.findAll();
        }

        public List<Motorcycle> listMotorcyclesByCapacity(int capacity, IMotoObserver client)
        {
            return this.motorcycles.findByCapacity(capacity);
        }

        public List<Participant> findParticipantForRace(int motorcycleId, IMotoObserver client)
        {
            return this.participants.findByMotorcycleId(motorcycleId);
        }

        public List<Motorcycle> listMotorcyclesByBrand(String brand, IMotoObserver client)
        {
            return this.motorcycles.findByBrand(brand);
        }

        public Motorcycle findMotorcycleById(int motorcycleId, IMotoObserver client)
        {
            return this.motorcycles.findById(motorcycleId);
        }

        public void addParticipant(String participantName, String motorcycleBrand, int motorcycleCapacity, IMotoObserver client)
        {
            int maximumId = 0;
            List<Participant> participantList = this.participants.findAll().ToList();
            foreach (Participant participant in participantList)
            {
                if (participant.Id > maximumId)
                {
                    maximumId = participant.Id;
                }
            }

            List<Motorcycle> motorcycleListByBrand = this.listMotorcyclesByBrand(motorcycleBrand, client);
            List<Motorcycle> motorcycleListByCapacity = this.listMotorcyclesByCapacity(motorcycleCapacity, client);
            try
            {
                Motorcycle motorcycle = motorcycleListByBrand.Distinct().Where(motorcycleItem => motorcycleListByCapacity.Contains(motorcycleItem)).First();
                Participant participant = new Participant();
                participant.Id = maximumId + 1;
                participant.Name = participantName;
                participant.MotorcycleID = motorcycle.Id;
                this.participants.save(participant);
                notifyOthersParticipantAdded(participant);
            }
            catch (Exception exception)
            {
                Console.Write(exception.StackTrace);
            }
        }

        private void notifyOthersParticipantAdded(Participant participant)
        {
            IEnumerable<User> users = this.users.findAll();
            foreach (User user in users)
            {
                if (this.loggedClients.ContainsKey(user.Id))
                {
                    IMotoObserver motoClient = this.loggedClients[user.Id];
                    Task.Run(() => motoClient.participantAdded(participant));
                }
            }
        }
    }
}