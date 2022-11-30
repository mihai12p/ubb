package socialnetwork.domain;

import java.time.LocalDateTime;
import java.util.Objects;

/**
 * {@code Friendship} is a subclass for users' friendships. It extends {@code Entity} with type parameter {@code <Integer>}.
 */
public class Friendship extends Entity<Integer>
{
    /**
     * Specific details that defines a friendship between between 2 users.
     */
    private int idUser1;
    private int idUser2;
    LocalDateTime friendsFrom;

    public Friendship(int idUser1, int idUser2, LocalDateTime friendsFrom)
    {
        this.idUser1 = idUser1;
        this.idUser2 = idUser2;
        this.friendsFrom = friendsFrom;
    }

    public int getIdUser1()
    {
        return this.idUser1;
    }

    public int getIdUser2()
    {
        return this.idUser2;
    }

    public LocalDateTime getFriendsFrom()
    {
        return this.friendsFrom;
    }

    public void setIdUser1(int idUser1)
    {
        this.idUser1 = idUser1;
    }

    public void setIdUser2(int idUser2)
    {
        this.idUser2 = idUser2;
    }

    public void setFriendsFrom(LocalDateTime friendsFrom)
    {
        this.friendsFrom = friendsFrom;
    }

    @Override
    public String toString()
    {
        return "Friendship{" +
                "idUser1=" + idUser1 +
                ", idUser2=" + idUser2 +
                ", friendsFrom=" + friendsFrom +
                '}';
    }

    /**
     * Method that verifies if 2 friendship refers to the same friendship based on its {@code idUser1}, {@code idUser2} and {@code friendsFrom}.
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
        if (!(o instanceof Friendship))
        {
            return false;
        }

        Friendship friendship = (Friendship)o;
        return (this.getIdUser1() == friendship.getIdUser1() && this.getIdUser2() == friendship.getIdUser2() ||
                this.getIdUser2() == friendship.getIdUser1() && this.getIdUser1() == friendship.getIdUser2()) &&
                getFriendsFrom().equals(friendship.getFriendsFrom());
    }

    /**
     * Method that returns a unique {@code int} for a friendship based on its {@code idUser1}, {@code idUser2} and {@code friendsFrom}.
     */
    @Override
    public int hashCode()
    {
        return Objects.hash(this.getIdUser1(), this.getIdUser2(), this.getFriendsFrom());
    }
}
