package socialnetwork.service;

import socialnetwork.Config;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.validator.FriendshipValidator;
import socialnetwork.domain.validator.UserValidator;
import socialnetwork.domain.validator.ValidationException;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.FriendshipInDatabase;
import socialnetwork.repository.database.UserInDatabase;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.Optional;

/**
 * {@code Service} is the class that coordinates the behaviour of the application.
 */
public class Service
{
    /**
     * Repository containg {@code User}s with the ID of type {@code Integer}.
     */
    private final Repository<Integer, User> userRepository;
    private final Repository<Integer, Friendship> friendshipRepository;

    public Service()
    {
        this.userRepository = new UserInDatabase(Config.getProperty("database_url"), Config.getProperty("database_username"), Config.getProperty("database_password"), new UserValidator());
        this.friendshipRepository = new FriendshipInDatabase(Config.getProperty("database_url"), Config.getProperty("database_username"), Config.getProperty("database_password"), new FriendshipValidator());
    }

    /**
     * Adds a user to the repository. It creates a user based on the information provided as parameters and sets its ID to the next value on the repository.
     * If the user already exists and is not deleted then a new one won't be added, if one exists but is deleted then it will be restored.
     * @return     does not return
     * @param      FirstName    User's first name
     * @param      LastName     User's last name
     * @param      Age          User's age
     * @param      Email        User's email
     * @throws     ValidationException if the {@code User}
     *             does not meet its defined requirements
     * @throws     IllegalArgumentException if the data read is not in the correct format
     */
    public boolean addUser(String FirstName, String LastName, int Age, String Email, String username, String password) throws IllegalArgumentException, ValidationException
    {
        User newUser = new User();
        newUser.setFirstName(FirstName);
        newUser.setLastName(LastName);
        newUser.setAge(Age);
        newUser.setEmail(Email);
        newUser.setUsername(username);
        newUser.setPassword(password);
        newUser.setId(newUser.hashCode());
        Optional<User> savedUser = this.userRepository.save(newUser);
        if (savedUser.isEmpty())
        {
            System.out.println(newUser + " has been successfully added.");
        }
        else
        {
            if (savedUser.get() != newUser && savedUser.get().isDeleted())
            {
                savedUser.get().setDeleted(false);
                this.userRepository.update(savedUser.get());
                System.out.println(savedUser.get() + " is back to life.");
            }
            else
            {
                System.out.println(newUser + " has not been added.");
                return false;
            }
        }
        return true;
    }

    /**
     * Searches a user in the repository.
     * @return     User if a user is found it's not deleted, null otherwise
     * @param      ID    User's ID
     * @throws     IllegalArgumentException if the data read is not in the correct format
     */
    private User searchUser(int ID) throws IllegalArgumentException
    {
        Optional<User> searchedUser = this.userRepository.findOne(ID);
        if (searchedUser.isEmpty())
        {
            System.out.println("An user with ID " + ID + " could not been found.");
            return null;
        }

        return searchedUser.get();
    }

    public User searchUser(String username) throws IllegalArgumentException
    {
        User searchedUser = new User();
        searchedUser.setUsername(username);
        return searchUser(searchedUser.hashCode());
    }

    private Friendship searchFriendship(int ID1, int ID2)
    {
        for (Friendship searchedFriendship : this.friendshipRepository.findAll())
        {
            if (searchedFriendship.getIdUser1() == ID1 || searchedFriendship.getIdUser2() == ID1)
            {
                if (searchedFriendship.getIdUser1() == ID2 || searchedFriendship.getIdUser2() == ID2)
                {
                    return searchedFriendship;
                }
            }
        }

        return null;
    }

    public Friendship searchFriendshipRequest(String username1, String username2)
    {
        User user1 = new User();
        user1.setUsername(username1);
        User user2 = new User();
        user2.setUsername(username2);
        for (Friendship searchedFriendshipRequest : this.friendshipRepository.findAll())
        {
            if (searchedFriendshipRequest.getIdUser1() == user1.hashCode() && searchedFriendshipRequest.getIdUser2() == user2.hashCode())
            {
                return searchedFriendshipRequest;
            }
        }

        return null;
    }

    /**
     * Creates a friendship between 2 users.
     * @return     does not return
     * @param      username1    User's username
     * @param      username2    User2's username
     * @throws     IllegalArgumentException if the data read is not in the correct format
     */
    public void addFriendToUser(String username1, String username2) throws IllegalArgumentException
    {
        User existingUser = this.searchUser(username1);
        User existingUser2 = this.searchUser(username2);
        if (existingUser != null && existingUser2 != null && !existingUser.equals(existingUser2))
        {
            if (this.searchFriendshipRequest(username1, username2) == null)
            {
                Friendship newFriendshipRequest = new Friendship(existingUser.getId(), existingUser2.getId(), LocalDateTime.now().truncatedTo(ChronoUnit.SECONDS));
                newFriendshipRequest.setId(newFriendshipRequest.hashCode());
                this.friendshipRepository.save(newFriendshipRequest);
                System.out.println("Friend request has been sent.");
            }
            else
            {
                System.out.println("They are friends already.");
            }
        }
    }

    /**
     * Destroy a friendship between 2 users.
     * @return     does not return
     * @param      username1    User's username
     * @param      username2    User2's username
     * @throws     IllegalArgumentException if the data read is not in the correct format
     */
    public void removeFriendFromUser(String username1, String username2) throws IllegalArgumentException
    {
        User existingUser = this.searchUser(username1);
        User existingUser2 = this.searchUser(username2);
        if (existingUser != null && existingUser2 != null && !existingUser.equals(existingUser2))
        {
            Friendship friendship = this.searchFriendship(existingUser.getId(), existingUser2.getId());
            if (friendship != null)
            {
                this.friendshipRepository.remove(friendship.getId());
                System.out.println("They are not friends anymore.");
            }
        }
    }

    public ArrayList<User> getFriendsOfUser(User user)
    {
        ArrayList<User> requestsOfUser = new ArrayList<>();
        ArrayList<User> requestsForUser = new ArrayList<>();
        this.friendshipRepository.findAll().forEach(friendship ->
        {
            if (friendship.getIdUser1() == user.getId())
            {
                User searchedUser = this.searchUser(friendship.getIdUser2());
                if (searchedUser != null && !searchedUser.isDeleted())
                {
                    requestsOfUser.add(searchedUser);
                }
            }
            else if (friendship.getIdUser2() == user.getId())
            {
                User searchedUser = this.searchUser(friendship.getIdUser1());
                if (searchedUser != null && !searchedUser.isDeleted())
                {
                    requestsForUser.add(searchedUser);
                }
            }
        });
        ArrayList<User> friendsOfUser = new ArrayList<>();
        for (User user1 : requestsOfUser)
        {
            for (User user2 : requestsForUser)
            {
                if (user1.equals(user2))
                {
                    friendsOfUser.add(user1);
                }
            }
        }
        return friendsOfUser;
    }

    public ArrayList<User> getFriendRequestsOfUser(User user)
    {
        ArrayList<User> requestsOfUser = new ArrayList<>();
        ArrayList<User> requestsForUser = new ArrayList<>();
        this.friendshipRepository.findAll().forEach(friendship ->
        {
            if (friendship.getIdUser1() == user.getId())
            {
                User searchedUser = this.searchUser(friendship.getIdUser2());
                if (searchedUser != null && !searchedUser.isDeleted())
                {
                    requestsOfUser.add(searchedUser);
                }
            }
            else if (friendship.getIdUser2() == user.getId())
            {
                User searchedUser = this.searchUser(friendship.getIdUser1());
                if (searchedUser != null && !searchedUser.isDeleted())
                {
                    requestsForUser.add(searchedUser);
                }
            }
        });
        ArrayList<User> friendRequests = new ArrayList<>();
        for (User user1 : requestsOfUser)
        {
            boolean friends = false;
            for (User user2 : requestsForUser)
            {
                if (user1.equals(user2))
                {
                    friends = true;
                    break;
                }
            }
            if (!friends)
            {
                friendRequests.add(user1);
            }
        }
        for (User user2 : requestsForUser)
        {
            boolean friends = false;
            for (User user1 : requestsOfUser)
            {
                if (user1.equals(user2))
                {
                    friends = true;
                    break;
                }
            }
            if (!friends)
            {
                friendRequests.add(user2);
            }
        }

        return friendRequests;
    }

    public Optional<User> verifyUserDetails(String username)
    {
        User user = new User();
        user.setUsername(username);
        return this.userRepository.findOne(user.hashCode());
    }
}
