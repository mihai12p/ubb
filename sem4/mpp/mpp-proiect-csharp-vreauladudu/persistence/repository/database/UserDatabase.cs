using mpp_proiect_csharp_vreauladudu.domain;
using System;
using System.Data.SQLite;

namespace mpp_proiect_csharp_vreauladudu.repository.database
{
    public class UserDatabase : AbstractDatabase<int, User>, UserRepository
    {
        public UserDatabase() : base("Users") { }

        protected override User extractEntity(SQLiteDataReader result)
        {   
            int id = Convert.ToInt32(result["id"]);
            String username = Convert.ToString(result["username"]);
            String password = Convert.ToString(result["password"]);

            User user = new User();
            user.Id = id;
            user.Username = username;
            user.Password = password;
            return user;
        }

        protected override SQLiteCommand findStatement(int id)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "SELECT * FROM Users WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@id", id));
            return command;
        }

        protected override SQLiteCommand saveStatement(User user)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "INSERT INTO Users(id, username, password) VALUES (@id, @username, @password)";
            command.Parameters.Add(new SQLiteParameter("@id", user.Id));
            command.Parameters.Add(new SQLiteParameter("@username", user.Username));
            command.Parameters.Add(new SQLiteParameter("@password", user.Password));
            return command;
        }

        protected override SQLiteCommand deleteStatement(int id)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "DELETE FROM Users WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@id", id));
            return command;
        }

        protected override SQLiteCommand updateStatement(User user)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "UPDATE Users SET [username] = @username, [password] = @password WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@username", user.Username));
            command.Parameters.Add(new SQLiteParameter("@password", user.Password));
            command.Parameters.Add(new SQLiteParameter("@id", user.Id));
            return command;
        }

        public User isValidUser(String username, String password)
        {
            using (SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand())
            {
                command.CommandText = "SELECT * FROM Users WHERE [username] = @username AND [password] = @password";
                command.Parameters.Add(new SQLiteParameter("@username", username));
                command.Parameters.Add(new SQLiteParameter("@password", password));

                using (SQLiteDataReader result = command.ExecuteReader())
                {
                    return result.Read() ? this.extractEntity(result) : null;
                }
            }
        }
    }
}