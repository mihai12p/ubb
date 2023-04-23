package moto.repository;

import moto.Entity;

public interface IRepository<ID, E extends Entity<ID>>
{
    E find(ID id);
    Iterable<E> findAll();
    E save(E entity);
    E remove(ID id);
    E update(E entity);
}