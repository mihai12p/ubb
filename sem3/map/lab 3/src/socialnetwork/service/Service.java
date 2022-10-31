package socialnetwork.service;

import socialnetwork.Config;
import socialnetwork.domain.User;
import socialnetwork.domain.validator.UserValidator;
import socialnetwork.domain.validator.ValidationException;
import socialnetwork.repository.Repository;
import socialnetwork.repository.file.UserInFile;

import java.util.HashSet;

/**
 * {@code Service} is the class that coordinates the behaviour of the application.
 */
public class Service
{
    /**
     * Repository containg {@code User}s with the ID of type {@code Integer}.
     */
    private final Repository<Integer, User> repository;

    public Service()
    {
        this.repository = new UserInFile(Config.getProperties().getProperty("Users"), new UserValidator());
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
        newUser.setId(this.repository.size() + 1);

        User savedUser = this.repository.save(newUser);
        if (savedUser == null)
        {
            System.out.println(newUser + " has been successfully added.");
        }
        else
        {
            if (savedUser != newUser && savedUser.isDeleted())
            {
                savedUser.setDeleted(false);
                System.out.println(savedUser + " is back to life.");
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
            existingUser.setDeleted(true);
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
        User searchedUser = this.repository.findOne(ID);
        if (searchedUser == null)
        {
            System.out.println("An user with ID " + ID + " could not been found.");
        }
        else if (searchedUser.isDeleted())
        {
            System.out.println("The user " + searchedUser + " has been deleted.");
            return null;
        }

        return searchedUser;
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
            existingUser.getFriends().add(existingUser2);
            this.repository.update(existingUser);

            existingUser2.getFriends().add(existingUser);
            this.repository.update(existingUser2);
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
            existingUser.getFriends().remove(existingUser2);
            this.repository.update(existingUser);

            existingUser2.getFriends().remove(existingUser);
            this.repository.update(existingUser2);
        }
    }

    private void DFS(User user)
    {
        user.setInCommunity(true);
        user.getFriends().forEach(friend ->
        {
            if (!friend.isInCommunity() && !friend.isDeleted())
            {
                DFS(friend);
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
        for (User user : this.repository.findAll())
        {
            if (!user.isInCommunity() && !user.isDeleted())
            {
                ++comunities;
                DFS(user);
            }
        }

        this.repository.findAll().forEach(user ->
        {
            user.setInCommunity(false);
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

        user.getFriends().forEach(friend ->
        {
            if (!friend.isInCommunity() && !friend.isDeleted())
            {
                DFS2(friend);
                friend.setInCommunity(false);
            }
        });

        if (this.sociableCommunityLength > this.mostSociableCommunityLength)
        {
            mostSociableCommunity.clear();
            this.repository.findAll().forEach(userInCommunity ->
            {
                if (userInCommunity.isInCommunity())
                {
                    mostSociableCommunity.add(userInCommunity);
                }
            });
            this.mostSociableCommunityLength = this.sociableCommunityLength;
        }

        --this.sociableCommunityLength;
        user.setInCommunity(false);
    }

    /**
     * Calculates the maximum length of users in a connected community.
     * @return     the maximum length of users
     */
    public void mostSociableCommunity()
    {
        this.sociableCommunityLength = 0;
        this.mostSociableCommunityLength = -1;
        this.repository.findAll().forEach(user ->
        {
            if (!user.isInCommunity() && !user.isDeleted())
            {
                DFS2(user);
            }
        });

        this.repository.findAll().forEach(user ->
        {
            user.setInCommunity(false);
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
        this.repository.findAll().forEach(user ->
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
        this.repository.findAll().forEach(user ->
        {
            if (!user.isDeleted())
            {
                System.out.println(user);
                user.getFriends().forEach(friend ->
                {
                    if (!friend.isDeleted())
                    {
                        System.out.println("\t" + friend);
                    }
                });
            }
        });
    }
}
