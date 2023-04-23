package moto.repository.database;

import moto.User;
import moto.repository.UserRepository;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;

public class UserDatabase extends AbstractDatabase<Integer, User> implements UserRepository
{
    public UserDatabase(Properties properties)
    {
        super(properties, "Users");
    }

    @Override
    protected User extractEntity(ResultSet resultSet) throws SQLException
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
    protected PreparedStatement findStatement(Integer id) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("SELECT * from Users WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(User user) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("INSERT INTO Users(id, username, password) VALUES (?, ?, ?)");
        statement.setInt(1, user.getId());
        statement.setString(2, user.getUsername());
        statement.setString(3, user.getPassword());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Integer id) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("DELETE FROM Users WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(User user) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("UPDATE Users SET username = ?, password = ? WHERE id = ?");
        statement.setString(1, user.getUsername());
        statement.setString(2, user.getPassword());
        statement.setInt(3, user.getId());
        return statement;
    }

    @Override
    public User isValidUser(String username, String password) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("SELECT * FROM Users WHERE username = ? AND password = ?");
        statement.setString(1, username);
        statement.setString(2, password);
        ResultSet resultSet = statement.executeQuery();
        return resultSet.next() ? this.extractEntity(resultSet) : null;
    }
}