package moto.repository;

import moto.Participant;

import java.sql.SQLException;
import java.util.List;

public interface ParticipantRepository extends IRepository<Integer, Participant>
{
    List<Participant> findByMotorcycleId(Integer motorcycleId) throws SQLException;
}