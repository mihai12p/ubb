package moto.domain;

public class Motorcycle extends Entity<Integer>
{
    private String brand;
    private MotorcycleCapacity capacity;

    public String getBrand()
    {
        return this.brand;
    }

    public void setBrand(String brand)
    {
        this.brand = brand;
    }

    public MotorcycleCapacity getCapacity()
    {
        return this.capacity;
    }

    public void setCapacity(MotorcycleCapacity capacity)
    {
        this.capacity = capacity;
    }

    @Override
    public String toString() {
        return "Motorcycle{" +
                "id='" + this.getId() + '\'' +
                ", brand='" + this.brand + '\'' +
                ", capacity=" + this.capacity +
                '}';
    }
}