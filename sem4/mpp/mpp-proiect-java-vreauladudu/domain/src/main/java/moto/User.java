package moto;

import javax.persistence.*;

@javax.persistence.Entity
@Table(name = "Users")
public class User extends Entity<Integer>
{
    private String username;
    private String password;

    @Override
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "id", updatable = false, nullable = false)
    public Integer getId()
    {
        return super.getId();
    }

    @Override
    public void setId(Integer id)
    {
        super.setId(id);
    }

    @Column(name = "username")
    public String getUsername()
    {
        return this.username;
    }

    public void setUsername(String username)
    {
        this.username = username;
    }

    @Column(name = "password")
    public String getPassword()
    {
        return this.password;
    }

    public void setPassword(String password)
    {
        this.password = password;
    }
}