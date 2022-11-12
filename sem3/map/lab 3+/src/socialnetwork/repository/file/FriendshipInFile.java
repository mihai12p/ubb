package socialnetwork.repository.file;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.validator.ValidatorStrategy;

import java.time.LocalDateTime;
import java.util.List;

public class FriendshipInFile extends AbstractInFile<Integer, Friendship>
{
    public FriendshipInFile(String fileName, ValidatorStrategy<Friendship> validator)
    {
        super(fileName, validator);
    }

    @Override
    public Friendship getEntity(List<String> attributes)
    {
        Friendship friendship = new Friendship(Integer.parseInt(attributes.get(1)), Integer.parseInt(attributes.get(2)), LocalDateTime.parse(attributes.get(3)));
        friendship.setId(Integer.parseInt(attributes.get(0)));

        return friendship;
    }

    @Override
    protected String entityAsString(Friendship friendship)
    {
        return friendship.getId() + ";" + friendship.getIdUser1() + ";" + friendship.getIdUser2() + ";" + friendship.getFriendsFrom();
    }
}
