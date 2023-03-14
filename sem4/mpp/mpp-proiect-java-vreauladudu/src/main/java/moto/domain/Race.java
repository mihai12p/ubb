package moto.domain;

import java.util.List;

public class Race extends Entity<Integer>
{
    private MotorcycleCategory motorcycleCategory;
    private List<Participant> participants;

    public MotorcycleCategory getMotorcycleCategory()
    {
        return this.motorcycleCategory;
    }

    public void setMotorcycleCategory(MotorcycleCategory motorcycleCategory)
    {
        this.motorcycleCategory = motorcycleCategory;
    }
}