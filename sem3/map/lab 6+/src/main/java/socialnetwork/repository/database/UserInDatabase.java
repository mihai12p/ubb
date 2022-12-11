package socialnetwork.repository.database;

import socialnetwork.domain.User;
import socialnetwork.domain.validator.ValidatorStrategy;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.util.Optional;

public class UserInDatabase extends AbstractInDatabase<Integer, User> implements Repository<Integer, User>
{
    public UserInDatabase(String url, String username, String password, ValidatorStrategy<User> validator)
    {
        super(url, username, password, "users", validator);
    }

    @Override
    public Optional<User> extractEntity(ResultSet resultSet) throws SQLException
    {
        Integer id = resultSet.getInt("id");
        String firstName = resultSet.getString("first_name");
        String lastName = resultSet.getString("last_name");
        int age = resultSet.getInt("age");
        String email = resultSet.getString("email");
        boolean isDeleted = resultSet.getBoolean("isdeleted");
        boolean isInCommunity = resultSet.getBoolean("isincommunity");
        String username = resultSet.getString("username");
        String password = resultSet.getString("password");

        User user = new User();
        user.setFirstName(firstName);
        user.setLastName(lastName);
        user.setAge(age);
        user.setEmail(email);
        user.setId(id);
        user.setDeleted(isDeleted);
        user.setInCommunity(isInCommunity);
        user.setUsername(username);
        user.setPassword(password);
        return Optional.of(user);
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("SELECT * from users WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, User user) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("INSERT INTO users(id, first_name, last_name, age, email, username, password) VALUES (?, ?, ?, ?, ?, ?, ?)");
        statement.setInt(1, user.getId());
        statement.setString(2, user.getFirstName());
        statement.setString(3, user.getLastName());
        statement.setInt(4, user.getAge());
        statement.setString(5, user.getEmail());
        statement.setString(6, user.getUsername());
        statement.setString(7, user.getPassword());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("UPDATE users SET isdeleted = ? WHERE id = ?");
        statement.setBoolean(1, true);
        statement.setInt(2, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, User user) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("UPDATE users SET first_name = ?, last_name = ?, age = ?, email = ?, isdeleted = ?, isincommunity = ?, username = ?, password = ? WHERE id = ?");
        statement.setString(1, user.getFirstName());
        statement.setString(2, user.getLastName());
        statement.setInt(3, user.getAge());
        statement.setString(4, user.getEmail());
        statement.setBoolean(5, user.isDeleted());
        statement.setBoolean(6, user.isInCommunity());
        statement.setString(7, user.getUsername());
        statement.setString(8, user.getPassword());
        statement.setInt(9, user.getId());
        return statement;
    }
}
