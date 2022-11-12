package socialnetwork.repository.memory;

import socialnetwork.domain.Entity;
import socialnetwork.domain.validator.ValidationException;
import socialnetwork.domain.validator.ValidatorStrategy;
import socialnetwork.repository.Repository;

import java.util.HashMap;
import java.util.Map;

/**
 * {@code InMemory} is the base class used for managing the entities in memory.
 *
 * @param      <ID></ID>   the type of {@code Entity}'s ID
 * @param      <E></E>     the type of {@code Entity} that has to be managed
 */
public class InMemory<ID, E extends Entity<ID>> implements Repository<ID, E>
{
    private final HashMap<ID, E> entities;
    private final ValidatorStrategy<E> validator;

    public InMemory(ValidatorStrategy<E> validator)
    {
        this.entities = new HashMap<ID, E>();
        this.validator = validator;
    }

    @Override
    public E findOne(ID id) throws IllegalArgumentException
    {
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        return this.entities.get(id);
    }

    @Override
    public Iterable<E> findAll()
    {
        return this.entities.values();
    }

    @Override
    public E save(E entity) throws IllegalArgumentException, ValidationException
    {
        if (entity == null)
        {
            throw new IllegalArgumentException("entity must not be null");
        }

        this.validator.validate(entity);

        for (Map.Entry<ID, E> entry : this.entities.entrySet())
        {
            if (entry.getValue().equals(entity))
            {
                return entry.getValue();
            }
        }

        if (this.entities.containsKey(entity.getId()))
        {
            return entity;
        }

        this.entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E remove(ID id)
    {
        return this.entities.remove(id);
    }

    @Override
    public E update(E entity) throws IllegalArgumentException, ValidationException
    {
        if (entity == null)
        {
            throw new IllegalArgumentException("entity must not be null");
        }

        this.validator.validate(entity);

        if (this.entities.containsKey(entity.getId()))
        {
            this.entities.put(entity.getId(), entity);
            return null;
        }

        return entity;
    }

    @Override
    public int size()
    {
        return this.entities.size();
    }
}
