package socialnetwork.repository.database;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.validator.ValidatorStrategy;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.util.Optional;

public class FriendshipInDatabase extends AbstractInDatabase<Integer, Friendship> implements Repository<Integer, Friendship>
{
    public FriendshipInDatabase(String url, String username, String password, ValidatorStrategy<Friendship> validator)
    {
        super(url, username, password, "friendships", validator);
    }

    @Override
    public Optional<Friendship> extractEntity(ResultSet resultSet) throws SQLException
    {
        Integer id1 = resultSet.getInt("iduser1");
        Integer id2 = resultSet.getInt("iduser2");
        Timestamp friendsFrom = resultSet.getTimestamp("friends_from");
        Integer id = resultSet.getInt("id");

        Friendship friendship = new Friendship(id1, id2, friendsFrom.toLocalDateTime());
        friendship.setId(id);
        return Optional.of(friendship);
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("SELECT * from friendships WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, Friendship friendship) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("INSERT INTO friendships(iduser1, iduser2, friends_from, id) VALUES (?, ?, ?, ?)");
        statement.setInt(1, friendship.getIdUser1());
        statement.setInt(2, friendship.getIdUser2());
        statement.setDate(3, Date.valueOf(friendship.getFriendsFrom().toLocalDate()));
        statement.setInt(4, friendship.getId());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("DELETE FROM friendships WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, Friendship friendship) throws SQLException
    {
        return null;
    }
}
