using mpp_proiect_csharp_vreauladudu.domain;
using System;
using System.Data.SQLite;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu.repository.database
{
    public class MotorcycleDatabase : AbstractDatabase<int, Motorcycle>, MotorcycleRepository
    {
        public MotorcycleDatabase() : base("Motorcycles") { }

        protected override Motorcycle extractEntity(SQLiteDataReader result)
        {   
            int id = Convert.ToInt32(result["id"]);
            String brand = Convert.ToString(result["brand"]);
            int capacity = Convert.ToInt32(result["capacity"]);

            Motorcycle motorcycle = new Motorcycle();
            motorcycle.Id = id;
            motorcycle.Brand = brand;
            motorcycle.Capacity = capacity;
            return motorcycle;
        }

        protected override SQLiteCommand findStatement(int id)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "SELECT * FROM Motorcycles WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@id", id));
            return command;
        }

        protected override SQLiteCommand saveStatement(Motorcycle motorcycle)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "INSERT INTO Motorcycles(id, brand, capacity) VALUES (@id, @brand, @capacity)";
            command.Parameters.Add(new SQLiteParameter("@id", motorcycle.Id));
            command.Parameters.Add(new SQLiteParameter("@brand", motorcycle.Brand));
            command.Parameters.Add(new SQLiteParameter("@capacity", motorcycle.Capacity));
            return command;
        }

        protected override SQLiteCommand deleteStatement(int id)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "DELETE FROM Motorcycles WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@id", id));
            return command;
        }

        protected override SQLiteCommand updateStatement(Motorcycle motorcycle)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "UPDATE Motorcycles SET [brand] = @brand, [capacity] = @capacity WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@brand", motorcycle.Brand));
            command.Parameters.Add(new SQLiteParameter("@capacity", motorcycle.Capacity));
            command.Parameters.Add(new SQLiteParameter("@id", motorcycle.Id));
            return command;
        }

        public List<Motorcycle> findByCapacity(int Capacity)
        {
            List<Motorcycle> motorcycles = new List<Motorcycle>();

            using (SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand())
            {
                command.CommandText = "SELECT * from Motorcycles WHERE [capacity] = @capacity";
                command.Parameters.Add(new SQLiteParameter("@capacity", Capacity));
                using (SQLiteDataReader result = command.ExecuteReader())
                {
                    while (result.Read())
                    {
                        motorcycles.Add(this.extractEntity(result));
                    }
                    return motorcycles;
                }
            }
        }

        public List<Motorcycle> findByBrand(String Brand)
        {
            List<Motorcycle> motorcycles = new List<Motorcycle>();

            using (SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand())
            {
                command.CommandText = "SELECT * from Motorcycles WHERE [brand] = @brand";
                command.Parameters.Add(new SQLiteParameter("@brand", Brand));

                using (SQLiteDataReader result = command.ExecuteReader())
                {
                    while (result.Read())
                    {
                        motorcycles.Add(this.extractEntity(result));
                    }
                    return motorcycles;
                }
            }
        }

        public Motorcycle findById(int Id)
        {
            using (SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand())
            {
                command.CommandText = "SELECT * from Motorcycles WHERE [id] = @id";
                command.Parameters.Add(new SQLiteParameter("@id", Id));

                using (SQLiteDataReader result = command.ExecuteReader())
                {
                    return result.Read() ? this.extractEntity(result) : null;
                }
            }
        }
    }
}