package socialnetwork.repository.file;

import socialnetwork.domain.User;
import socialnetwork.domain.validator.ValidatorStrategy;

import java.util.List;

/**
 * {@code UserInFile} is a subclass of {@code AbstractInFile} for managing reading
 * from file for {@code User}s.
 */
public class UserInFile extends AbstractInFile<Integer, User>
{
    public UserInFile(String fileName, ValidatorStrategy<User> validator)
    {
        super(fileName, validator);
    }

    @Override
    public User getEntity(List<String> attributes)
    {
        User user = new User(attributes.get(1), attributes.get(2), Integer.parseInt(attributes.get(3)), attributes.get(4));
        user.setId(Integer.parseInt(attributes.get(0)));
        user.setDeleted(Boolean.parseBoolean(attributes.get(5)));

        return user;
    }

    @Override
    protected String entityAsString(User user)
    {
        return user.getId() + ";" + user.getFirstName() + ";" + user.getLastName() + ";" + user.getAge() + ";" + user.getEmail() + ";" + user.isDeleted();
    }
}
