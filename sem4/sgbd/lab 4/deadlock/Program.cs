using System.Data;
using System.Data.SqlClient;

namespace deadlock
{
    internal static class Program
    {
        private static readonly String ConnectionString = "Server=--\\SQLEXPRESS;Database=Motorshop;Integrated Security=true;";

        static void Main()
        {
            ThreadPool.QueueUserWorkItem(Proc1);
            ThreadPool.QueueUserWorkItem(Proc2);

            Console.Read();
        }

        static void Proc1(Object? stateInfo)
        {
            using (SqlConnection Connection = new SqlConnection(ConnectionString))
            {
                using (SqlCommand command = new SqlCommand("DeadLockProc1", Connection))
                {
                    command.CommandType = CommandType.StoredProcedure;

                    Connection.Open();

                    int retries = 3;
                    while (true)
                    {
                        try
                        {
                            Console.WriteLine("Locking Clients");
                            Console.WriteLine("Clients locked");
                            int rowsAffected = command.ExecuteNonQuery();
                            Console.WriteLine("No deadlock");
                            break;
                        }
                        catch (SqlException exception) when (exception.Number == 1205)
                        {
                            Console.WriteLine("Deadlock");
                            if (--retries == 0)
                            {
                                throw;
                            }
                        }
                    }
                }
            }
        }

        static void Proc2(Object? stateInfo)
        {
            Thread.Sleep(1000);

            using (SqlConnection Connection = new SqlConnection(ConnectionString))
            {
                using (SqlCommand command = new SqlCommand("DeadLockProc2", Connection))
                {
                    command.CommandType = CommandType.StoredProcedure;

                    Connection.Open();

                    int retries = 3;
                    while (true)
                    {
                        try
                        {
                            Console.WriteLine("\t\t\t\tLocking ClientsMoto");
                            Console.WriteLine("\t\t\t\tClientsMoto locked");
                            int rowsAffected = command.ExecuteNonQuery();
                            Console.WriteLine("\t\t\t\tNo deadlock");
                            break;
                        }
                        catch (SqlException exception) when (exception.Number == 1205)
                        {
                            Console.WriteLine("\t\t\t\tDeadlock");
                            if (--retries == 0)
                            {
                                throw;
                            }
                        }
                    }
                }
            }
        }
    }
}