package socialnetwork.repository.database;

import socialnetwork.domain.Entity;
import socialnetwork.domain.validator.ValidationException;
import socialnetwork.domain.validator.ValidatorStrategy;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public abstract class AbstractInDatabase<ID, E extends Entity<ID>> implements Repository<ID, E>
{
    private final String url;
    private final String username;
    private final String password;
    private final String table;
    private final ValidatorStrategy<E> validator;

    public AbstractInDatabase(String url, String username, String password, String table, ValidatorStrategy<E> validator)
    {
        this.url = url;
        this.username = username;
        this.password = password;
        this.table = table;
        this.validator = validator;
    }

    private Connection getConnection() throws SQLException
    {
        return DriverManager.getConnection(url, username, password);
    }

    public abstract Optional<E> extractEntity(ResultSet resultSet) throws SQLException;

    protected abstract PreparedStatement findStatement(Connection connection, ID id) throws SQLException;
    protected abstract PreparedStatement saveStatement(Connection connection, E entity) throws SQLException;
    protected abstract PreparedStatement deleteStatement(Connection connection, ID id) throws SQLException;
    protected abstract PreparedStatement updateStatement(Connection connection, E entity) throws SQLException;

    @Override
    public Optional<E> findOne(ID id) throws IllegalArgumentException
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
        Set<E> entities = new HashSet<>();
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
    public Optional<E> save(E entity) throws ValidationException
    {
        this.validator.validate(entity);

        Optional<E> optEntity = this.findOne(entity.getId());
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
        return optEntity;
    }

    @Override
    public Optional<E> remove(ID id) throws IllegalArgumentException
    {
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        Optional<E> optEntity = this.findOne(id);
        if (optEntity.isPresent())
        {
            try (Connection connection = this.getConnection())
            {
                this.deleteStatement(connection, id).executeUpdate();
            } catch (SQLException exception)
            {
                exception.printStackTrace();
            }
        }
        return optEntity;
    }

    @Override
    public Optional<E> update(E entity) throws ValidationException
    {
        this.validator.validate(entity);

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

    @Override
    public int size()
    {
        return ((Collection<?>)this.findAll()).size();
    }
}
