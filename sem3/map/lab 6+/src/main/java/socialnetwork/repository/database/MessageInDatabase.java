package socialnetwork.repository.database;

import socialnetwork.domain.Message;
import socialnetwork.domain.validator.ValidatorStrategy;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.util.Optional;

public class MessageInDatabase extends AbstractInDatabase<Integer, Message> implements Repository<Integer, Message>
{
    public MessageInDatabase(String url, String username, String password, ValidatorStrategy<Message> validator)
    {
        super(url, username, password, "messages", validator);
    }

    @Override
    public Optional<Message> extractEntity(ResultSet resultSet) throws SQLException
    {
        Integer id = resultSet.getInt("id");
        Integer id1 = resultSet.getInt("iduser1");
        Integer id2 = resultSet.getInt("iduser2");
        String content = resultSet.getString("content");
        Timestamp date_sent = resultSet.getTimestamp("date_sent");

        Message message = new Message(id1, id2, content, date_sent);
        message.setId(id);
        return Optional.of(message);
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("SELECT * from messages WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, Message message) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("INSERT INTO messages(id, iduser1, iduser2, content, date_sent) VALUES (?, ?, ?, ?, ?)");
        statement.setInt(1, message.getId());
        statement.setInt(2, message.getIdUser1());
        statement.setInt(3, message.getIdUser2());
        statement.setString(4, message.getContent());
        statement.setTimestamp(5, message.getDate_sent());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("DELETE FROM messages WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, Message message) throws SQLException
    {
        return null;
    }
}
