package moto.repository.database;

import moto.domain.Motorcycle;
import moto.domain.MotorcycleCapacity;
import moto.repository.IRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MotorcycleDatabase extends AbstractDatabase<Integer, Motorcycle> implements IRepository<Integer, Motorcycle>
{
    public MotorcycleDatabase(String host, String username, String password)
    {
        super(host, username, password, "Motorcycles");
    }

    @Override
    public Motorcycle extractEntity(ResultSet resultSet) throws SQLException
    {
        Integer id = resultSet.getInt("id");
        String brand = resultSet.getString("brand");
        MotorcycleCapacity capacity = MotorcycleCapacity.valueOf(resultSet.getString("capacity"));

        Motorcycle motorcycle = new Motorcycle();
        motorcycle.setId(id);
        motorcycle.setBrand(brand);
        motorcycle.setCapacity(capacity);
        return motorcycle;
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("SELECT * from Motorcycles WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, Motorcycle motorcycle) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("INSERT INTO Motorcycles(id, brand, capacity) VALUES (?, ?, ?)");
        statement.setInt(1, motorcycle.getId());
        statement.setString(2, motorcycle.getBrand());
        statement.setObject(3, motorcycle.getCapacity());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, Integer id) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("DELETE FROM Motorcycles WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, Motorcycle motorcycle) throws SQLException
    {
        PreparedStatement statement = connection.prepareStatement("UPDATE Motorcycles SET brand = ?, capacity = ? WHERE id = ?");
        statement.setString(1, motorcycle.getBrand());
        statement.setObject(2, motorcycle.getCapacity());
        statement.setInt(3, motorcycle.getId());
        return statement;
    }
}