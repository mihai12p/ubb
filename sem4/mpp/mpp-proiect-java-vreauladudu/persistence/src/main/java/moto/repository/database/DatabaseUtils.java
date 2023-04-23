package moto.repository.database;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class DatabaseUtils
{
    private static Properties properties;
    private static Connection connection = null;

    private static final Logger logger = LogManager.getLogger();

    public static void setProperties(Properties properties)
    {
        DatabaseUtils.properties = properties;
    }

    public static Connection getConnection() throws SQLException
    {
        try
        {
            logger.traceEntry();
            if (connection == null || connection.isClosed())
            {
                String host = properties.getProperty("jdbc.url");
                String username = properties.getProperty("jdbc.user");
                String password = properties.getProperty("jdbc.pass");

                logger.info("trying to connect to database ... {}", host);
                logger.info("user: {}", username);
                logger.info("password: {}", password);

                if (username != null && password != null)
                {
                    connection = DriverManager.getConnection(host, username, password);
                }
                else
                {
                    connection = DriverManager.getConnection(host);
                }
            }
        }
        catch (SQLException exception)
        {
            logger.error(exception);
            exception.printStackTrace();
        }

        logger.traceExit();
        return connection;
    }
}