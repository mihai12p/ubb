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
import socialnetwork.repository.file.FriendshipInFile;
import socialnetwork.repository.file.UserInFile;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.HashSet;
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
    public void addUser(String FirstName, String LastName, int Age, String Email) throws IllegalArgumentException, ValidationException
    {
        User newUser = new User(FirstName, LastName, Age, Email);
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
            }
        }
    }

    /**
     * Searches a user in the repository. If one exists, it marks the user as deleted. The user is not removed from the repository.
     * @return     does not return
     * @param      ID    User's ID
     * @throws     IllegalArgumentException if the data read is not in the correct format
     */
    public void removeUser(int ID) throws IllegalArgumentException
    {
        User existingUser = this.searchUser(ID);
        if (existingUser != null)
        {
            this.userRepository.remove(ID);
        }
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

    /**
     * Creates a friendship between 2 users.
     * @return     does not return
     * @param      ID    User's ID
     * @param      ID2   User2's ID
     * @throws     IllegalArgumentException if the data read is not in the correct format
     */
    public void addFriendToUser(int ID, int ID2) throws IllegalArgumentException
    {
        User existingUser = this.searchUser(ID);
        User existingUser2 = this.searchUser(ID2);
        if (existingUser != null && existingUser2 != null)
        {
            if (this.searchFriendship(ID, ID2) == null)
            {
                Friendship newFriendship = new Friendship(ID, ID2, LocalDateTime.now().truncatedTo(ChronoUnit.SECONDS));
                newFriendship.setId(newFriendship.hashCode());
                this.friendshipRepository.save(newFriendship);
                System.out.println("They are friends now.");
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
     * @param      ID    User's ID
     * @param      ID2   User2's ID
     * @throws     IllegalArgumentException if the data read is not in the correct format
     */
    public void removeFriendFromUser(int ID, int ID2) throws IllegalArgumentException
    {
        User existingUser = this.searchUser(ID);
        User existingUser2 = this.searchUser(ID2);
        if (existingUser != null && existingUser2 != null)
        {
            Friendship friendship = this.searchFriendship(ID, ID2);
            if (friendship != null)
            {
                this.friendshipRepository.remove(friendship.getId());
                System.out.println("They are not friends anymore.");
            }
            else
            {
                System.out.println("They are not friends already.");
            }
        }
    }

    private void DFS(User user)
    {
        user.setInCommunity(true);
        this.userRepository.update(user);
        this.friendshipRepository.findAll().forEach(friendship ->
        {
            if (friendship.getIdUser1() == user.getId())
            {
                User friend = this.searchUser(friendship.getIdUser2());
                if (friend != null && !friend.isInCommunity() && !friend.isDeleted())
                {
                    DFS(friend);
                }
            }
            else if (friendship.getIdUser2() == user.getId())
            {
                User friend = this.searchUser(friendship.getIdUser1());
                if (friend != null && !friend.isInCommunity() && !friend.isDeleted())
                {
                    DFS(friend);
                }
            }
        });
    }

    /**
     * Counts the number of connected communities among users. Starting from every user, it adds to the same community all its friends. The process continues for all the users.
     * @return     the number of communities
     */
    public int numberOfComunities()
    {
        int comunities = 0;
        for (User user : this.userRepository.findAll())
        {
            User updatedUser = this.searchUser(user.getId());
            if (!updatedUser.isInCommunity() && !updatedUser.isDeleted())
            {
                ++comunities;
                DFS(updatedUser);
            }
        }

        this.userRepository.findAll().forEach(user ->
        {
            user.setInCommunity(false);
            this.userRepository.update(user);
        });

        return comunities;
    }

    private int sociableCommunityLength = 0;
    private int mostSociableCommunityLength = -1;
    private final HashSet<User> mostSociableCommunity = new HashSet<>();
    private void DFS2(User user)
    {
        ++this.sociableCommunityLength;
        user.setInCommunity(true);
        this.userRepository.update(user);

        this.friendshipRepository.findAll().forEach(friendship ->
        {
            if (friendship.getIdUser1() == user.getId())
            {
                User friend = this.searchUser(friendship.getIdUser2());
                if (friend != null && !friend.isInCommunity() && !friend.isDeleted())
                {
                    DFS2(friend);
                    friend.setInCommunity(false);
                    this.userRepository.update(friend);
                }
            }
            else if (friendship.getIdUser2() == user.getId())
            {
                User friend = this.searchUser(friendship.getIdUser1());
                if (friend != null && !friend.isInCommunity() && !friend.isDeleted())
                {
                    DFS2(friend);
                    friend.setInCommunity(false);
                    this.userRepository.update(friend);
                }
            }
        });

        if (this.sociableCommunityLength > this.mostSociableCommunityLength)
        {
            mostSociableCommunity.clear();
            this.userRepository.findAll().forEach(userInCommunity ->
            {
                User updatedUser = this.searchUser(userInCommunity.getId());
                if (updatedUser.isInCommunity())
                {
                    mostSociableCommunity.add(updatedUser);
                }
            });
            this.mostSociableCommunityLength = this.sociableCommunityLength;
        }

        --this.sociableCommunityLength;
        user.setInCommunity(false);
        this.userRepository.update(user);
    }

    /**
     * Calculates the maximum length of users in a connected community.
     * @return     the maximum length of users
     */
    public void mostSociableCommunity()
    {
        this.sociableCommunityLength = 0;
        this.mostSociableCommunityLength = -1;
        this.userRepository.findAll().forEach(user ->
        {
            User updatedUser = this.searchUser(user.getId());
            if (!updatedUser.isInCommunity() && !updatedUser.isDeleted())
            {
                DFS2(updatedUser);
            }
        });

        this.userRepository.findAll().forEach(user ->
        {
            user.setInCommunity(false);
            this.userRepository.update(user);
        });

        System.out.println("The most sociable community has " + this.mostSociableCommunityLength + " users:");
        mostSociableCommunity.forEach(user ->
        {
            System.out.println("\t" + user);
        });
    }

    /**
     * Prints all the users without their friends.
     * @return     does not return
     */
    public void listUsers()
    {
        this.userRepository.findAll().forEach(user ->
        {
            if (!user.isDeleted())
            {
                System.out.println(user);
            }
        });
    }

    /**
     * Prints all the users including their friends.
     * @return     does not return
     */
    public void listUsersWithFriends()
    {
        this.userRepository.findAll().forEach(user ->
        {
            if (!user.isDeleted())
            {
                System.out.println(user);
                this.friendshipRepository.findAll().forEach(friendship ->
                {
                    if (friendship.getIdUser1() == user.getId())
                    {
                        User searchedUser = this.searchUser(friendship.getIdUser2());
                        if (searchedUser != null && !searchedUser.isDeleted())
                        {
                            System.out.println("\t" + this.searchUser(friendship.getIdUser2()));
                        }
                    }
                    else if (friendship.getIdUser2() == user.getId())
                    {
                        User searchedUser = this.searchUser(friendship.getIdUser1());
                        if (searchedUser != null && !searchedUser.isDeleted())
                        {
                            System.out.println("\t" + this.searchUser(friendship.getIdUser1()));
                        }
                    }
                });
            }
        });
    }
}
