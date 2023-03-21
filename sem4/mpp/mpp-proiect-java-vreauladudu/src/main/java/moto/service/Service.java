package moto.service;

import moto.configuration.DatabaseConfig;
import moto.domain.*;
import moto.repository.IRepository;
import moto.repository.database.MotorcycleDatabase;
import moto.repository.database.ParticipantDatabase;
import moto.repository.database.UserDatabase;

import java.util.Properties;

public class Service
{
    private final IRepository<Integer, Motorcycle> motorcycles;
    private final IRepository<Integer, Participant> participants;
    private final IRepository<Integer, User> users;

    public Service()
    {
        this.motorcycles = new MotorcycleDatabase(DatabaseConfig.getProperty("jdbc.url"), DatabaseConfig.getProperty("jdbc.user"), DatabaseConfig.getProperty("jdbc.pass"));
        this.participants = new ParticipantDatabase(DatabaseConfig.getProperty("jdbc.url"), DatabaseConfig.getProperty("jdbc.user"), DatabaseConfig.getProperty("jdbc.pass"));
        this.users = new UserDatabase(DatabaseConfig.getProperty("jdbc.url"), DatabaseConfig.getProperty("jdbc.user"), DatabaseConfig.getProperty("jdbc.pass"));
    }

    public void listMotorcycles()
    {
        this.motorcycles.findAll().forEach(System.out::println);
    }

    public void listParticipants()
    {
        this.participants.findAll().forEach(System.out::println);
    }

    public void listUsers()
    {
        this.users.findAll().forEach(System.out::println);
    }
}
