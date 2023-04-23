package moto;

import java.util.Objects;

public class Motorcycle extends Entity<Integer>
{
    private String brand;
    private Integer capacity;

    public String getBrand()
    {
        return this.brand;
    }

    public void setBrand(String brand)
    {
        this.brand = brand;
    }

    public Integer getCapacity()
    {
        return this.capacity;
    }

    public void setCapacity(Integer capacity)
    {
        this.capacity = capacity;
    }

    @Override
    public String toString() {
        return "ID: " + this.getId() + " | Brand: " + this.getBrand() + " | Capacitate: " + this.getCapacity();
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o)
        {
            return true;
        }
        if (o == null || getClass() != o.getClass())
        {
            return false;
        }
        Motorcycle that = (Motorcycle) o;
        return Objects.equals(getId(), that.getId());
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(getId(), getBrand(), getCapacity());
    }
}