package moto.domain;

public class Participant extends Entity<Integer>
{
    private String name;
    private Integer motorcycleID;

    public String getName()
    {
        return this.name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public Integer getMotorcycleID()
    {
        return this.motorcycleID;
    }

    public void setMotorcycleID(Integer motorcycleID)
    {
        this.motorcycleID = motorcycleID;
    }

    @Override
    public String toString() {
        return "Participant{" +
                "id='" + this.getId() + '\'' +
                ", name='" + this.name + '\'' +
                ", motorcycleID=" + this.motorcycleID +
                '}';
    }
}