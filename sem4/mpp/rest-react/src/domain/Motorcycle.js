class Motorcycle
{
    constructor(id, brand, capacity)
    {
        this.id = id;
        this.brand = brand;
        this.capacity = capacity;
    }
  
    toString()
    {
        return `ID: ${this.id} | Brand: ${this.brand} | Capacitate: ${this.capacity}`;
    }
  
    equals(other)
    {
        if (this === other) 
        {
            return true;
        }
        if (other === null || !(other instanceof Motorcycle))
        {
            return false;
        }
        return this.id === other.id;
    }
  
    hashCode()
    {
        return this.id;
    }
}
  
export default Motorcycle;