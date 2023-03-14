package moto.repository.database;

import moto.domain.Entity;
import moto.repository.IRepository;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;

public abstract class AbstractDatabase<ID, E extends Entity<ID>> implements IRepository<ID, E>
{
    private final String host;
    private final String username;
    private final String password;
    private final String table;

    public AbstractDatabase(String host, String username, String password, String table)
    {
        this.host = host;
        this.username = username;
        this.password = password;
        this.table = table;
    }

    private Connection getConnection() throws SQLException
    {
        return DriverManager.getConnection(this.host, this.username, this.password);
    }

    public abstract Optional<E> extractEntity(ResultSet resultSet) throws SQLException;

    protected abstract PreparedStatement findStatement(Connection connection, ID id) throws SQLException;
    protected abstract PreparedStatement saveStatement(Connection connection, E entity) throws SQLException;
    protected abstract PreparedStatement deleteStatement(Connection connection, ID id) throws SQLException;
    protected abstract PreparedStatement updateStatement(Connection connection, E entity) throws SQLException;

    @Override
    public Optional<E> find(ID id) throws IllegalArgumentException
    {
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        try (Connection connection = this.getConnection())
        {
            ResultSet resultSet = findStatement(connection, id).executeQuery();
            if (resultSet.next())
            {
                return extractEntity(resultSet);
            }
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<E> findAll()
    {
        HashSet<E> entities = new HashSet<>();
        try (Connection connection = this.getConnection())
        {
            ResultSet resultSet = connection.prepareStatement("SELECT * from " + this.table).executeQuery();
            while (resultSet.next())
            {
                this.extractEntity(resultSet).ifPresent(entities::add);
            }
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
        return entities;
    }

    @Override
    public Optional<E> save(E entity)
    {
        Optional<E> optEntity = this.find(entity.getId());
        if (optEntity.isPresent())
        {
            return optEntity;
        }

        try (Connection connection = this.getConnection())
        {
            this.saveStatement(connection, entity).executeUpdate();
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
        return this.find(entity.getId());
    }

    @Override
    public Optional<E> remove(ID id) throws IllegalArgumentException
    {
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        Optional<E> optEntity = this.find(id);
        if (optEntity.isPresent())
        {
            try (Connection connection = this.getConnection())
            {
                this.deleteStatement(connection, id).executeUpdate();
            }
            catch (SQLException exception)
            {
                exception.printStackTrace();
            }
        }
        return optEntity;
    }

    @Override
    public Optional<E> update(E entity)
    {
        try (Connection connection = this.getConnection())
        {
            this.updateStatement(connection, entity).executeUpdate();
        }
        catch (SQLException exception)
        {
            exception.printStackTrace();
        }
        return Optional.of(entity);
    }
}
