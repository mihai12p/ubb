package socialnetwork.domain;

import java.io.Serializable;

/**
 * {@code Entity} is a superclass for all entities. It implements {@code Serializable} so every entity can be serialized.
 *
 * @param      <ID></ID>   the type of {@code Entity}'s ID
 */
public class Entity<ID> implements Serializable
{
    @java.io.Serial
    private static final long serialVersionUID = 12345678L;

    private ID id;

    public ID getId() { return this.id; }

    public void setId(ID id) { this.id = id; }
}
