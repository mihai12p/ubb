package moto.repository.database;

import moto.Entity;
import moto.repository.IRepository;

import java.sql.*;
import java.util.HashSet;
import java.util.Properties;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public abstract class AbstractDatabase<ID, E extends Entity<ID>> implements IRepository<ID, E>
{
    private final String table;
    private static final Logger logger = LogManager.getLogger();

    public AbstractDatabase(Properties properties, String table)
    {
        DatabaseUtils.setProperties(properties);
        this.table = table;
    }

    protected abstract E extractEntity(ResultSet resultSet) throws SQLException;

    protected abstract PreparedStatement findStatement(ID id) throws SQLException;
    protected abstract PreparedStatement saveStatement(E entity) throws SQLException;
    protected abstract PreparedStatement deleteStatement(ID id) throws SQLException;
    protected abstract PreparedStatement updateStatement(E entity) throws SQLException;

    @Override
    public E find(ID id) throws IllegalArgumentException
    {
        logger.traceEntry();
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        try
        {
            ResultSet resultSet = findStatement(id).executeQuery();
            if (resultSet.next())
            {
                E entity = this.extractEntity(resultSet);
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
        try
        {
            ResultSet resultSet = DatabaseUtils.getConnection().prepareStatement("SELECT * FROM " + this.table).executeQuery();
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

        try
        {
            this.saveStatement(entity).executeUpdate();
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
            try
            {
                this.deleteStatement(id).executeUpdate();
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
        try
        {
            this.updateStatement(entity).executeUpdate();
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