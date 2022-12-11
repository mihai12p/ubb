package socialnetwork.domain.validator;

import socialnetwork.domain.Friendship;

/**
 * The class {@code FriendshipValidator} is a form of
 * {@code ValidatorStrategy} used to validate the {@code Entity}
 * of type {@code Friendship}.
 */
public class FriendshipValidator implements ValidatorStrategy<Friendship>
{
    /**
     * Validates a {@code Friendship}.
     * Firstly, a Friendship's {@code ID1}, {@code ID2}, {@code FriendsFrom} should not be null or blank.
     *
     * @param      friendship   the {@code Friendship} that has to be validated
     * @return     does not return
     * @throws     ValidationException if the {@code Friendship}
     *             does not meet its defined requirements
     */
    @Override
    public void validate(Friendship friendship) throws ValidationException
    {
        String errorMessages = "";
        if (friendship.getId() == null)
        {
            errorMessages += "ID error: " + friendship.getId() + "\n";
        }

        if (friendship.getIdUser1() == 0)
        {
            errorMessages += "ID user1 error: " + friendship.getIdUser1() + "\n";
        }

        if (friendship.getIdUser2() == 0)
        {
            errorMessages += "ID user2 error: " + friendship.getIdUser2() + "\n";
        }

        if (friendship.getFriendsFrom() == null)
        {
            errorMessages += "ID friendsFrom error: " + friendship.getFriendsFrom() + "\n";
        }

        if (errorMessages != "")
        {
            throw new ValidationException(errorMessages);
        }
    }
}
