package moto.services;

import moto.Motorcycle;
import moto.Participant;
import moto.User;

import java.util.List;
import java.util.Map;

public interface IMotoService
{
    void login(User user, IMotoObserver client) throws MotoException;
    void logout(User user, IMotoObserver client) throws MotoException;
    Map<Integer, List<Motorcycle>> listRaces(IMotoObserver client) throws MotoException;
    Iterable<Motorcycle> listMotorcycles(IMotoObserver client) throws MotoException;
    List<Motorcycle> listMotorcyclesByCapacity(Integer capacity, IMotoObserver client) throws MotoException;
    List<Participant> findParticipantForRace(Integer motorcycleId, IMotoObserver client) throws MotoException;
    List<Motorcycle> listMotorcyclesByBrand(String brand, IMotoObserver client) throws MotoException;
    Motorcycle findMotorcycleById(Integer motorcycleId, IMotoObserver client) throws MotoException;
    void addParticipant(String participantName, String motorcycleBrand, Integer motorcycleCapacity, IMotoObserver client) throws MotoException;
}