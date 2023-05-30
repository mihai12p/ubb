const remove = async (entityId) =>
{
    try
    {
        const response = await fetch(`http://localhost:8080/moto/motorcycles/${entityId}`,
        {
            method: 'DELETE',
        });
        if (response.ok)
        {
            return;
        }
        else
        {
            console.error('fetch() failed with status ', response.status);
            throw new Error('fetch() failed');
        }
    }
    catch (error)
    {
        console.error('Error deleting entity:', error);
        throw error;
    }
};

export default remove;