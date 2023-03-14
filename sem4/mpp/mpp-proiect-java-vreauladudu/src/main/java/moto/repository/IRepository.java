package moto.repository;

import moto.domain.Entity;

import java.util.Optional;

public interface IRepository<ID, E extends Entity<ID>>
{
    Optional<E> find(ID id);
    Iterable<E> findAll();
    Optional<E> save(E entity);
    Optional<E> remove(ID id);
    Optional<E> update(E entity);
}