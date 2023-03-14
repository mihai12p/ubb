package moto.domain;

public class Motorcycle extends Entity<Integer>
{
    private String brand;
    private Float capacity;

    public String getBrand()
    {
        return this.brand;
    }

    public void setBrand(String brand)
    {
        this.brand = brand;
    }

    public Float getCapacity()
    {
        return this.capacity;
    }

    public void setCapacity(Float capacity)
    {
        this.capacity = capacity;
    }
}