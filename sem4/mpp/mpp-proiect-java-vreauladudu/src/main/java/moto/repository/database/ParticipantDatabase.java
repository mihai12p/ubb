package moto.repository.database;

import moto.domain.Participant;
import moto.repository.IRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ParticipantDatabase extends AbstractDatabase<Integer, Participant> implements IRepository<Integer, Participant>
{
    public ParticipantDatabase(String host, String username, String password)
    {
        super(host, username, password, "Participants");
    }

    @Override
    public Participant extractEntity(ResultSet resultSet) throws SQLException
    {
        Integer id = resultSet.getInt("id");
        String name = resultSet.getString("name");
        Integer motorcycleID = resultSet.getInt("mID");

        Participant participant = new Participant();
        participant.setId(id);
        participant.setName(name);
        participant.setMotorcycleID(motorcycleID);
        return participant;
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("SELECT * from Participants WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, Participant participant) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("INSERT INTO Participants(id, name, mID) VALUES (?, ?, ?)");
        statement.setInt(1, participant.getId());
        statement.setString(2, participant.getName());
        statement.setObject(3, participant.getMotorcycleID());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("DELETE FROM Participants WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, Participant participant) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("UPDATE Participants SET name = ?, mID = ? WHERE id = ?");
        statement.setString(1, participant.getName());
        statement.setObject(2, participant.getMotorcycleID());
        statement.setInt(3, participant.getId());
        return statement;
    }
}