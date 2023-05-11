package moto.repository.database;

import moto.Motorcycle;
import moto.repository.MotorcycleRepository;
import org.springframework.stereotype.Component;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

@Component
public class MotorcycleDatabase extends AbstractDatabase<Integer, Motorcycle> implements MotorcycleRepository
{
    public MotorcycleDatabase(Properties properties)
    {
        super(properties, "Motorcycles");
    }

    @Override
    protected Motorcycle extractEntity(ResultSet resultSet) throws SQLException
    {
        Integer id = resultSet.getInt("id");
        String brand = resultSet.getString("brand");
        Integer capacity = resultSet.getInt("capacity");

        Motorcycle motorcycle = new Motorcycle();
        motorcycle.setId(id);
        motorcycle.setBrand(brand);
        motorcycle.setCapacity(capacity);
        return motorcycle;
    }

    @Override
    protected PreparedStatement findStatement(Integer id) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("SELECT * from Motorcycles WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement saveStatement(Motorcycle motorcycle) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("INSERT INTO Motorcycles(id, brand, capacity) VALUES (?, ?, ?)");
        statement.setInt(1, motorcycle.getId());
        statement.setString(2, motorcycle.getBrand());
        statement.setInt(3, motorcycle.getCapacity());
        return statement;
    }

    @Override
    protected PreparedStatement deleteStatement(Integer id) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("DELETE FROM Motorcycles WHERE id = ?");
        statement.setInt(1, id);
        return statement;
    }

    @Override
    protected PreparedStatement updateStatement(Motorcycle motorcycle) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("UPDATE Motorcycles SET brand = ?, capacity = ? WHERE id = ?");
        statement.setString(1, motorcycle.getBrand());
        statement.setInt(2, motorcycle.getCapacity());
        statement.setInt(3, motorcycle.getId());
        return statement;
    }

    @Override
    public List<Motorcycle> findByCapacity(Integer Capacity) throws SQLException
    {
        List<Motorcycle> motorcycles = new ArrayList<>();

        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("SELECT * from Motorcycles WHERE capacity = ?");
        statement.setInt(1, Capacity);
        ResultSet resultSet = statement.executeQuery();
        while (resultSet.next())
        {
            motorcycles.add(this.extractEntity(resultSet));
        }
        return motorcycles;
    }

    @Override
    public List<Motorcycle> findByBrand(String Brand) throws SQLException
    {
        List<Motorcycle> motorcycles = new ArrayList<>();

        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("SELECT * from Motorcycles WHERE brand = ?");
        statement.setString(1, Brand);
        ResultSet resultSet = statement.executeQuery();
        while (resultSet.next())
        {
            motorcycles.add(this.extractEntity(resultSet));
        }
        return motorcycles;
    }

    @Override
    public Motorcycle findById(Integer Id) throws SQLException
    {
        PreparedStatement statement = DatabaseUtils.getConnection().prepareStatement("SELECT * from Motorcycles WHERE id = ?");
        statement.setInt(1, Id);
        ResultSet resultSet = statement.executeQuery();
        return resultSet.next() ? this.extractEntity(resultSet) : null;
    }
}