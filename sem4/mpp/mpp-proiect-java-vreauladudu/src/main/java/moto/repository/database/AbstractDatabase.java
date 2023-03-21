package moto.repository.database;

import moto.domain.Entity;
import moto.repository.IRepository;

import java.sql.*;
import java.util.HashSet;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public abstract class AbstractDatabase<ID, E extends Entity<ID>> implements IRepository<ID, E>
{
    private final String host;
    private final String username;
    private final String password;
    private final String table;
    private static final Logger logger = LogManager.getLogger();

    public AbstractDatabase(String host, String username, String password, String table)
    {
        this.host = host;
        this.username = username;
        this.password = password;
        this.table = table;
    }

    private Connection getConnection() throws SQLException
    {
        logger.traceEntry();
        logger.info("trying to connect to database ... {}", this.host);
        logger.info("user: {}", this.username);
        logger.info("password: {}", this.password);
        logger.traceExit();
        if (this.username != null && this.password != null)
        {
            return DriverManager.getConnection(this.host, this.username, this.password);
        }
        else
        {
            return DriverManager.getConnection(this.host);
        }
    }

    public abstract E extractEntity(ResultSet resultSet) throws SQLException;

    protected abstract PreparedStatement findStatement(Connection connection, ID id) throws SQLException;
    protected abstract PreparedStatement saveStatement(Connection connection, E entity) throws SQLException;
    protected abstract PreparedStatement deleteStatement(Connection connection, ID id) throws SQLException;
    protected abstract PreparedStatement updateStatement(Connection connection, E entity) throws SQLException;

    @Override
    public E find(ID id) throws IllegalArgumentException
    {
        logger.traceEntry();
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        try (Connection connection = this.getConnection())
        {
            ResultSet resultSet = findStatement(connection, id).executeQuery();
            if (resultSet.next())
            {
                E entity = extractEntity(resultSet);
                logger.traceExit(entity);
                return entity;
            }
        }
        catch (SQLException exception)
        {
            logger.error(exception);
            exception.printStackTrace();
        }
        logger.traceExit();
        return null;
    }

    @Override
    public Iterable<E> findAll()
    {
        logger.traceEntry();
        HashSet<E> entities = new HashSet<>();
        try (Connection connection = this.getConnection())
        {
            ResultSet resultSet = connection.prepareStatement("SELECT * from " + this.table).executeQuery();
            while (resultSet.next())
            {
                entities.add(this.extractEntity(resultSet));
            }
        }
        catch (SQLException exception)
        {
            logger.error(exception);
            exception.printStackTrace();
        }
        logger.traceExit(entities);
        return entities;
    }

    @Override
    public E save(E entity)
    {
        logger.traceEntry();
        E searchedEntity = this.find(entity.getId());
        if (searchedEntity != null)
        {
            logger.traceExit(searchedEntity);
            return searchedEntity;
        }

        try (Connection connection = this.getConnection())
        {
            this.saveStatement(connection, entity).executeUpdate();
        }
        catch (SQLException exception)
        {
            logger.error(exception);
            exception.printStackTrace();
        }

        E savedEntity = this.find(entity.getId());
        logger.traceExit(savedEntity);
        return savedEntity;
    }

    @Override
    public E remove(ID id) throws IllegalArgumentException
    {
        logger.traceEntry();
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        E searchedEntity = this.find(id);
        if (searchedEntity != null)
        {
            try (Connection connection = this.getConnection())
            {
                this.deleteStatement(connection, id).executeUpdate();
            }
            catch (SQLException exception)
            {
                logger.error(exception);
                exception.printStackTrace();
            }
        }
        logger.traceExit(searchedEntity);
        return searchedEntity;
    }

    @Override
    public E update(E entity)
    {
        logger.traceEntry();
        try (Connection connection = this.getConnection())
        {
            this.updateStatement(connection, entity).executeUpdate();
        }
        catch (SQLException exception)
        {
            logger.error(exception);
            exception.printStackTrace();
        }
        logger.traceExit(entity);
        return entity;
    }
}