package moto.repository;

import moto.Motorcycle;

import java.sql.SQLException;
import java.util.List;

public interface MotorcycleRepository extends IRepository<Integer, Motorcycle>
{
    List<Motorcycle> findByCapacity(Integer Capacity) throws SQLException;
    List<Motorcycle> findByBrand(String Brand) throws SQLException;
    Motorcycle findById(Integer Id) throws SQLException;
}