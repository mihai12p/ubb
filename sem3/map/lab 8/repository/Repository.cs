namespace lab_8.repository
{
    internal interface Repository<ID, E>
    {
        E? findOne(ID id);
        IEnumerable<E> findAll();
        E? save(E e);
        E? remove(ID id);
        E? update(E e);
    }
}