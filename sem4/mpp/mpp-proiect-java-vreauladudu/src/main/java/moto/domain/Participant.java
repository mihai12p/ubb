package moto.domain;

public class Participant extends Entity<Integer>
{
    private String name;
    private Motorcycle motorcycle;
    private Team team;

    public String getName()
    {
        return this.name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public Motorcycle getMotorcycle()
    {
        return this.motorcycle;
    }

    public void setMotorcycle(Motorcycle motorcycle)
    {
        this.motorcycle = motorcycle;
    }

    public Team getTeam()
    {
        return this.team;
    }

    public void setTeam(Team team)
    {
        this.team = team;
    }
}