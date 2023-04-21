using mpp_proiect_csharp_vreauladudu.domain;
using System;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu.service
{
    public interface IMotoService
    {
        void login(User user, IMotoObserver client);
        void logout(User user, IMotoObserver client);
        Dictionary<int, List<Motorcycle>> listRaces(IMotoObserver client);
        IEnumerable<Motorcycle> listMotorcycles(IMotoObserver client);
        List<Motorcycle> listMotorcyclesByCapacity(int capacity, IMotoObserver client);
        List<Participant> findParticipantForRace(int motorcycleId, IMotoObserver client);
        List<Motorcycle> listMotorcyclesByBrand(String brand, IMotoObserver client);
        Motorcycle findMotorcycleById(int motorcycleId, IMotoObserver client);
        void addParticipant(String participantName, String motorcycleBrand, int motorcycleCapacity, IMotoObserver client);
    }
}