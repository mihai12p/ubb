import Motorcycle from '../domain/Motorcycle';

const create = async (entityData) => 
{
    try 
    {
        const response = await fetch('http://localhost:8080/moto/motorcycles',
        {
            method: 'POST',
            headers: 
            {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(entityData),
        });
        if (response.ok)
        {
            const createdEntity = await response.json();
            const motorcycle = new Motorcycle(createdEntity.id, createdEntity.brand, createdEntity.capacity);
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
        console.error('Error creating entity:', error);
        throw error;
    }
};

export default create;