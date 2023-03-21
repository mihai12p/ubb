package moto.repository.database;

import moto.domain.User;
import moto.repository.IRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserDatabase extends AbstractDatabase<Integer, User> implements IRepository<Integer, User>
{
    public UserDatabase(String host, String username, String password)
    {
        super(host, username, password, "Users");
    }

    @Override
    public User extractEntity(ResultSet resultSet) throws SQLException
    {
        Integer id = resultSet.getInt("id");
        String username = resultSet.getString("username");
        String password = resultSet.getString("password");

        User user = new User();
        user.setId(id);
        user.setUsername(username);
        user.setPassword(password);
        return user;
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("SELECT * from Users WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, User user) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("INSERT INTO Users(id, username, password) VALUES (?, ?, ?)");
        statement.setInt(1, user.getId());
        statement.setString(2, user.getUsername());
        statement.setString(3, user.getPassword());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("DELETE FROM Users WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, User user) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("UPDATE Users SET username = ?, password = ? WHERE id = ?");
        statement.setString(1, user.getUsername());
        statement.setString(2, user.getPassword());
        statement.setInt(3, user.getId());
        return statement;
    }
}