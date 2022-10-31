package socialnetwork.domain;

import java.util.HashSet;
import java.util.Objects;

/**
 * {@code User} is a subclass for users. It extends {@code Entity} with type parameter {@code <Integer>}.
 */
public class User extends Entity<Integer>
{
    /**
     * Specific details that defines a user.
     */
    private int id;
    private String firstName;
    private String lastName;
    private int age = -1;
    private String email;
    private boolean deleted = false;
    private boolean inCommunity = false;

    /**
     * An unordered set that contains the friends of a user. It does not allow duplicates.
     */
    private HashSet<User> friends = new HashSet<>();

    public User(String firstName, String lastName, int age, String email)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
        this.email = email;
    }

    @Override
    public Integer getId()
    {
        return this.id;
    }

    public String getFirstName()
    {
        return this.firstName;
    }

    public String getLastName()
    {
        return this.lastName;
    }

    public int getAge()
    {
        return this.age;
    }

    public String getEmail() { return this.email; }

    public HashSet<User> getFriends()
    {
        return this.friends;
    }

    public boolean isDeleted() { return this.deleted; }

    public boolean isInCommunity() { return this.inCommunity; }

    @Override
    public void setId(Integer id)
    {
        this.id = id;
    }

    public void setFirstName(String firstName)
    {
        this.firstName = firstName;
    }

    public void setLastName(String lastName)
    {
        this.lastName = lastName;
    }

    public void setAge(int age)
    {
        this.age = age;
    }

    public void setEmail(String email)
    {
        this.email = email;
    }

    public void setDeleted(boolean deleted) { this.deleted = deleted; }

    public void setInCommunity(boolean inCommunity) { this.inCommunity = inCommunity; }

    @Override
    public String toString()
    {
        return "User{" +
                "id=" + this.getId() +
                ", firstName='" + this.firstName + '\'' +
                ", lastName='" + this.lastName + '\'' +
                ", age=" + this.age +
                '}';
    }

    /**
     * Method that verifies if 2 users refers to the same user based on its {@code FirstName}, {@code LastName} and {@code Email}.
     * @param      o   the {@code Object} that has to be compared with
     * @return     {@code true} if the users are equal, false otherwise
     */
    @Override
    public boolean equals(Object o)
    {
        if (this == o)
        {
            return true;
        }
        if (o == null || !(o instanceof User))
        {
            return false;
        }

        User user = (User)o;
        return this.getFirstName().equals(user.getFirstName()) && this.getLastName().equals(user.getLastName()) && this.getEmail().equals(user.getEmail());
    }

    /**
     * Method that returns a unique {@code int} for a user based on its {@code FirstName}, {@code LastName} and {@code Email}.
     */
    @Override
    public int hashCode()
    {
        return Objects.hash(this.getFirstName(), this.getLastName(), this.getEmail());
    }
}
