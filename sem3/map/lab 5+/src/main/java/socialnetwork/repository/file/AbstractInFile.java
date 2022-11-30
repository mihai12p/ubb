package socialnetwork.repository.file;

import socialnetwork.domain.Entity;
import socialnetwork.domain.validator.ValidationException;
import socialnetwork.domain.validator.ValidatorStrategy;
import socialnetwork.repository.memory.InMemory;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

/**
 * {@code AbstractInFile} is an abstract class for managing reading from file
 * for different types of entities.
 *
 * @param      <ID></ID>   the type of {@code Entity}'s ID
 * @param      <E></E>     the type of {@code Entity} that has to be managed
 */
public abstract class AbstractInFile<ID, E extends Entity<ID>> extends InMemory<ID, E>
{
    /**
     * File name where to read from.
     */
    private final String fileName;

    public AbstractInFile(String fileName, ValidatorStrategy<E> validator)
    {
        super(validator);
        this.fileName = fileName;
        this.loadData();
    }

    /**
     * Loads data of different types from a file.
     * @return     does not return
     * @throws     ValidationException if the {@code Entity}
     *             does not meet its defined requirements
     * @throws     IllegalArgumentException if the data read is not in the correct format
     */
    private void loadData() throws IllegalArgumentException, ValidationException
    {
        Path path = Paths.get(this.fileName);
        try
        {
            List<String> lines = Files.readAllLines(path);
            lines.forEach(line ->
            {
                E entity = this.getEntity(Arrays.asList(line.split(";")));
                super.save(entity);
            });
        }
        catch (IOException exception)
        {
            System.err.println("Error while reading the file: " + this.fileName);
            exception.printStackTrace();
        }
        catch (IllegalArgumentException | ValidationException | ArrayIndexOutOfBoundsException exception)
        {
            System.err.println(exception);
            exception.printStackTrace();
        }
    }

    /**
     * Abstract method that each {@code Entity} should tell how to be seen.
     * @return     E - {@code Entity}'s type
     * @param      attributes   the {@code Entity}'s specific attributes as a {@code List} of {@code String}s
     */
    protected abstract E getEntity(List<String> attributes);

    /**
     * Abstract method that each {@code Entity} should tell how to be seen as a String.
     * @return     String
     * @param      entity   the {@code Entity}
     */
    protected abstract String entityAsString(E entity);

    @Override
    public Optional<E> save(E entity)
    {
        Optional<E> e = super.save(entity);
        if (e.isEmpty())
        {
            this.saveToFile(entity);
        }
        return e;
    }

    @Override
    public Optional<E> update(E entity)
    {
        Optional<E> e = super.update(entity);
        if (e.isEmpty())
        {
            this.refreshFile(super.findAll());
        }
        return e;
    }

    @Override
    public Optional<E> remove(ID id)
    {
        Optional<E> e = super.remove(id);
        if (e.isPresent())
        {
            this.refreshFile(super.findAll());
        }
        return e;
    }

    /**
     * Writes the Entity seen as a String to file.
     * @return     does not return
     * @param      entity   the {@code Entity}
     */
    private void saveToFile(E entity)
    {
        try (BufferedWriter bW = new BufferedWriter(new FileWriter(this.fileName, true)))
        {
            bW.write(entityAsString(entity));
            bW.newLine();
        }
        catch (IOException exception)
        {
            exception.printStackTrace();
        }
    }

    private void refreshFile(Iterable<E> entities)
    {
        try (BufferedWriter bW = new BufferedWriter(new FileWriter(this.fileName, false)))
        {
            for (E entity : entities)
            {
                bW.write(entityAsString(entity));
                bW.newLine();
            }
        }
        catch (IOException exception)
        {
            exception.printStackTrace();
        }
    }

    @Override
    public int size()
    {
        return super.size();
    }
}
