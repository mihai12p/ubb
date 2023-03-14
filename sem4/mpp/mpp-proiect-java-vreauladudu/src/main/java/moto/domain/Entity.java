package moto.domain;

import java.io.Serializable;

public class Entity<ID> implements Serializable
{
    @java.io.Serial
    private static final long serialVersionUID = 123456789L;

    private ID id;

    public ID getId() { return this.id; }

    public void setId(ID id) { this.id = id; }
}