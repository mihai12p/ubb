package moto.server;

import moto.Motorcycle;
import moto.Participant;
import moto.User;
import moto.repository.MotorcycleRepository;
import moto.repository.ParticipantRepository;
import moto.repository.UserRepository;
import moto.services.IMotoObserver;
import moto.services.IMotoService;
import moto.services.MotoException;

import java.sql.SQLException;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class MotoServer implements IMotoService
{
    private MotorcycleRepository motorcycles;
    private ParticipantRepository participants;
    private UserRepository users;
    private Map<Integer, IMotoObserver> loggedClients;

    public MotoServer(MotorcycleRepository motorcycles, ParticipantRepository participants, UserRepository users)
    {
        this.motorcycles = motorcycles;
        this.participants = participants;
        this.users = users;
        this.loggedClients = new ConcurrentHashMap<>();
    }

    public synchronized void login(User user, IMotoObserver client) throws MotoException
    {
        try
        {
            User userToLogIn = this.users.isValidUser(user.getUsername(), user.getPassword());
            if (userToLogIn == null)
            {
                throw new MotoException("Authentication failed.");
            }

            if (this.loggedClients.get(userToLogIn.getId()) != null)
            {
                throw new MotoException("User already logged in.");
            }

            this.loggedClients.put(userToLogIn.getId(), client);
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
    }

    public synchronized void logout(User user, IMotoObserver client) throws MotoException
    {
        try
        {
            User userToLogOut = this.users.isValidUser(user.getUsername(), user.getPassword());
            if (userToLogOut == null)
            {
                throw new MotoException("Unexpected error.");
            }

            if (this.loggedClients.get(userToLogOut.getId()) == null)
            {
                throw new MotoException("User " + user + " is not logged in.");
            }

            this.loggedClients.remove(userToLogOut.getId());
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
    }

    public synchronized Map<Integer, List<Motorcycle>> listRaces(IMotoObserver client)
    {
        Iterable<Motorcycle> motorcycles = this.motorcycles.findAll();
        return StreamSupport.stream(motorcycles.spliterator(), false).collect(Collectors.groupingBy(Motorcycle::getCapacity));
    }

    public synchronized Iterable<Motorcycle> listMotorcycles(IMotoObserver client)
    {
        return this.motorcycles.findAll();
    }

    public synchronized List<Motorcycle> listMotorcyclesByCapacity(Integer capacity, IMotoObserver client)
    {
        try
        {
            return this.motorcycles.findByCapacity(capacity);
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
        return null;
    }

    public synchronized List<Participant> findParticipantForRace(Integer motorcycleId, IMotoObserver client)
    {
        try
        {
            return this.participants.findByMotorcycleId(motorcycleId);
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
        return null;
    }

    public synchronized List<Motorcycle> listMotorcyclesByBrand(String brand, IMotoObserver client)
    {
        try
        {
            return this.motorcycles.findByBrand(brand);
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
        return null;
    }

    public synchronized Motorcycle findMotorcycleById(Integer motorcycleId, IMotoObserver client)
    {
        try
        {
            return this.motorcycles.findById(motorcycleId);
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
        return null;
    }

    public synchronized void addParticipant(String participantName, String motorcycleBrand, Integer motorcycleCapacity, IMotoObserver client)
    {
        Integer maximumId = 0;
        Iterable<Participant> participantList = this.participants.findAll();
        for (Participant participant : participantList)
        {
            if (participant.getId() > maximumId)
            {
                maximumId = participant.getId();
            }
        }

        List<Motorcycle> motorcycleListByBrand = listMotorcyclesByBrand(motorcycleBrand, client);
        List<Motorcycle> motorcycleListByCapacity = listMotorcyclesByCapacity(motorcycleCapacity, client);
        Optional<Motorcycle> motorcycle = motorcycleListByBrand.stream().distinct().filter(motorcycleListByCapacity::contains).findFirst();
        if (motorcycle.isPresent())
        {
            Participant participant = new Participant();
            participant.setId(maximumId + 1);
            participant.setName(participantName);
            participant.setMotorcycleID(motorcycle.get().getId());
            this.participants.save(participant);
            this.notifyOthersParticipantAdded(participant);
        }
    }

    private synchronized void notifyOthersParticipantAdded(Participant participant)
    {
        ExecutorService executor = Executors.newFixedThreadPool(4);

        this.users.findAll().forEach(user ->
        {
            if (this.loggedClients.get(user.getId()) != null)
            {
                IMotoObserver motoClient = this.loggedClients.get(user.getId());
                executor.execute(() ->
                {
                    try
                    {
                        motoClient.participantAdded(participant);
                    }
                    catch (MotoException exception)
                    {
                        System.err.println("Moto exception in thread " + exception.getMessage());
                        exception.printStackTrace();
                    }
                });
            }
        });

        executor.shutdown();
    }
}