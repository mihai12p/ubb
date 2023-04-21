using mpp_proiect_csharp_vreauladudu.domain;
using System;
using System.Data.SQLite;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu.repository.database
{
    public class ParticipantDatabase : AbstractDatabase<int, Participant>, ParticipantRepository
    {
        public ParticipantDatabase() : base("Participants") { }

        protected override Participant extractEntity(SQLiteDataReader result)
        {   
            int id = Convert.ToInt32(result["id"]);
            String name = Convert.ToString(result["name"]);
            int motorcycleID = Convert.ToInt32(result["mID"]);

            Participant participant = new Participant();
            participant.Id = id;
            participant.Name = name;
            participant.MotorcycleID = motorcycleID;
            return participant;
        }

        protected override SQLiteCommand findStatement(int id)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "SELECT * FROM Participants WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@id", id));
            return command;
        }

        protected override SQLiteCommand saveStatement(Participant participant)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "INSERT INTO Participants(id, name, mID) VALUES (@id, @name, @mID)";
            command.Parameters.Add(new SQLiteParameter("@id", participant.Id));
            command.Parameters.Add(new SQLiteParameter("@name", participant.Name));
            command.Parameters.Add(new SQLiteParameter("@mID", participant.MotorcycleID));
            return command;
        }

        protected override SQLiteCommand deleteStatement(int id)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "DELETE FROM Participants WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@id", id));
            return command;
        }

        protected override SQLiteCommand updateStatement(Participant participant)
        {
            SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand();
            command.CommandText = "UPDATE Participants SET [name] = @name, [mID] = @mID WHERE [id] = @id";
            command.Parameters.Add(new SQLiteParameter("@name", participant.Name));
            command.Parameters.Add(new SQLiteParameter("@mID", participant.MotorcycleID));
            command.Parameters.Add(new SQLiteParameter("@id", participant.Id));
            return command;
        }

        public List<Participant> findByMotorcycleId(int motorcycleId)
        {
            List<Participant> participants = new List<Participant>();

            using (SQLiteCommand command = DatabaseUtils.GetConnection().CreateCommand())
            {
                command.CommandText = "SELECT * from Participants WHERE [mID] = @mID";
                command.Parameters.Add(new SQLiteParameter("@mID", motorcycleId));

                using (SQLiteDataReader result = command.ExecuteReader())
                {
                    while (result.Read())
                    {
                        participants.Add(this.extractEntity(result));
                    }
                    return participants;
                }
            }
        }
    }
}