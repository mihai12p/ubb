package socialnetwork.repository;

import socialnetwork.domain.Entity;

import java.util.Optional;

/**
 * {@code Repository} is the interface for managing different
 * types of entities.
 *
 * @param      <ID></ID>   the type of {@code Entity}'s ID
 * @param      <E></E>     the type of {@code Entity}
 */
public interface Repository<ID, E extends Entity<ID>>
{
    /**
     * Finds one {@code Entity} by an ID.
     *
     * @param      id   the type {@code Entity}'s ID
     * @return     E - the {@code Entity}
     */
    Optional<E> findOne(ID id);

    /**
     * Finds all the {@code Entity}s
     *
     * @return     {@code Iterable<E>} - the {@code Entities}
     */
    Iterable<E> findAll();

    /**
     * Saves one {@code Entity}.
     *
     * @param      entity   the {@code Entity} to be saved
     * @return     E - the {@code Entity} saved or the existing {@code Entity}
     */
    Optional<E> save(E entity);

    /**
     * Removes one {@code Entity}.
     *
     * @param      id   the {@code Entity}'s ID to be removed
     * @return     E - the {@code Entity} removed
     */
    Optional<E> remove(ID id);

    /**
     * Updates one {@code Entity} with another {@code Entity}.
     *
     * @param      entity   the {@code Entity} that will replace the current {@code Entity}
     * @return     E - the updated {@code Entity}
     */
    Optional<E> update(E entity);

    /**
     * Counts the number of {@code Entities}.
     *
     * @return     int - the number of {@code Entities}
     */
    int size();
}
