package socialnetwork.domain.validator;

/**
 * {@code ValidatorStrategy} is the interface for validating different
 * types of entities. Is uses the strategy pattern via generics.
 *
 * @param      <T></T>   the type of {@code Entity} that has to be validated
 */
public interface ValidatorStrategy<T>
{
    /**
     * Validates the {@code Entity} based on its type.
     *
     * @param      entity   the {@code Entity} that has to be validated
     * @return     does not return
     * @throws     ValidationException if the {@code Entity}
     *             does not meet its defined requirements
     */
    void validate(T entity) throws ValidationException;
}
