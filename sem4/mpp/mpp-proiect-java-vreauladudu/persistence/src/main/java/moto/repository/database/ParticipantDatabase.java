package moto.repository.database;

import moto.Participant;
import moto.repository.ParticipantRepository;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class ParticipantDatabase extends AbstractDatabase<Integer, Participant> implements ParticipantRepository
{
    public ParticipantDatabase(Properties properties)
    {
        super(properties, "Participants");
    }

    @Override
    protected Participant extractEntity(ResultSet resultSet) throws SQLException
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
    protected PreparedStatement findStatement(Integer id) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("SELECT * from Participants WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(Participant participant) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("INSERT INTO Participants(id, name, mID) VALUES (?, ?, ?)");
        statement.setInt(1, participant.getId());
        statement.setString(2, participant.getName());
        statement.setInt(3, participant.getMotorcycleID());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Integer id) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("DELETE FROM Participants WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(Participant participant) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("UPDATE Participants SET name = ?, mID = ? WHERE id = ?");
        statement.setString(1, participant.getName());
        statement.setInt(2, participant.getMotorcycleID());
        statement.setInt(3, participant.getId());
        return statement;
    }

    @Override
    public List<Participant> findByMotorcycleId(Integer motorcycleId) throws SQLException
    {
        List<Participant> participants = new ArrayList<>();

        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("SELECT * from Participants WHERE mID = ?");
        statement.setInt(1, motorcycleId);
        ResultSet resultSet = statement.executeQuery();
        while (resultSet.next())
        {
            participants.add(this.extractEntity(resultSet));
        }
        return participants;
    }
}