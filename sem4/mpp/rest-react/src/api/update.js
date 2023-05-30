import Motorcycle from '../domain/Motorcycle';

const update = async (entityData, entityId) =>
{
    try
    {
        const response = await fetch(`http://localhost:8080/moto/motorcycles/${entityId}`,
        {
            method: 'PUT',
            headers:
            {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(entityData),
        });
        if (response.ok)
        {
            const updatedEntity = await response.json();
            const motorcycle = new Motorcycle(updatedEntity.id, updatedEntity.brand, updatedEntity.capacity);
            return motorcycle;
        }
        else
        {
            console.error('fetch() failed with status ', response.status);
            throw new Error('fetch() failed');
        }
    }
    catch (error)
    {
        console.error('Error updating entity:', error);
        throw error;
    }
};

export default update;