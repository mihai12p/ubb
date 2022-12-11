package socialnetwork.domain.validator;

import socialnetwork.domain.User;

/**
 * The class {@code UserValidator} is a form of
 * {@code ValidatorStrategy} used to validate the {@code Entity}
 * of type {@code User}.
 */
public class UserValidator implements ValidatorStrategy<User>
{
    /**
     * Validates an {@code User}.
     * Firstly, a User's {@code ID}, {@code FirstName}, {@code LastName}, {@code Email} should not be null
     * or blank. The last third should also not contain a blank space. The {@code Age} must be in range of 1-150.
     * The {@code Email} should contain a '@' and a dot.
     *
     * @param      user   the {@code User} that has to be validated
     * @return     does not return
     * @throws     ValidationException if the {@code User}
     *             does not meet its defined requirements
     */
    @Override
    public void validate(User user) throws ValidationException
    {
        String errorMessages = "";
        if (user.getId() == null)
        {
            errorMessages += "ID error: " + user.getId() + "\n";
        }

        if (user.getFirstName() == null || "".equals(user.getFirstName()) || user.getFirstName().contains(" "))
        {
            errorMessages += "FirstName error: " + user.getFirstName() + "\n";
        }

        if (user.getLastName() == null || "".equals(user.getLastName()) || user.getLastName().contains(" "))
        {
            errorMessages += "LastName error: " + user.getLastName() + "\n";
        }

        if (user.getAge() <= 0 || user.getAge() > 150)
        {
            errorMessages += "Age error: " + user.getAge() + "\n";
        }

        if (user.getEmail() == null || "".equals(user.getEmail()) || user.getEmail().contains(" ") || !user.getEmail().contains("@") || !user.getEmail().contains("."))
        {
            errorMessages += "Email error: " + user.getEmail() + "\n";
        }

        if (user.getUsername() == null || "".equals(user.getUsername()) || user.getUsername().contains(" "))
        {
            errorMessages += "Username error: " + user.getUsername() + "\n";
        }

        if (user.getPassword() == null || "".equals(user.getPassword()) || user.getPassword().contains(" "))
        {
            errorMessages += "Password error: " + user.getPassword() + "\n";
        }

        if (errorMessages != "")
        {
            throw new ValidationException(errorMessages);
        }
    }
}
