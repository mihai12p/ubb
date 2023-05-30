import Motorcycle from '../domain/Motorcycle';

const findAll = async () =>
{
    try
    {
        const response = await fetch('http://localhost:8080/moto/motorcycles');
        if (response.ok)
        {
            const data = await response.json();
            const motorcycles = data.map((item) => 
            {
                return new Motorcycle(item.id, item.brand, item.capacity);
            });
            return motorcycles;
        }
        else
        {
            console.error('fetch() failed with status ', response.status);
            throw new Error('fetch() failed');
        }
    }
    catch (error)
    {
        console.error('Error fetching entities:', error);
        throw error;
    }
};

export default findAll;