package moto.service;

import moto.domain.*;
import moto.repository.IRepository;

public class Service
{
    private final IRepository<Integer, Motorcycle> motorcycles;
    private final IRepository<Integer, Participant> participants;
    private final IRepository<Integer, Team> teams;
    private final IRepository<Integer, Race> races;

    public Service()
    {

    }
}
