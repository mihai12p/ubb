using System;
using System.Data.SQLite;
using System.Configuration;

namespace mpp_proiect_csharp_vreauladudu.repository.database
{
    public class DatabaseUtils
    {
        private static readonly log4net.ILog logger = log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);
        private static SQLiteConnection connection = null;

        public static SQLiteConnection GetConnection()
        {
            try
            {
                logger.Info("Entry");
                if (connection == null || connection.State == System.Data.ConnectionState.Closed)
                {
                    connection = new SQLiteConnection(ConfigurationManager.ConnectionStrings["ConnectionInfo"].ConnectionString);
                    connection.Open();
                }
            }
            catch (SQLiteException exception)
            {
                logger.Error(exception.Message);
                Console.Write(exception.StackTrace);
            }

            logger.Info("Exit");
            return connection;
        }
    }
}