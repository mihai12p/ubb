package moto.configuration;

import java.io.FileReader;
import java.io.IOException;
import java.util.Objects;
import java.util.Properties;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class DatabaseConfig
{
    private static final String CONFIG_LOCATION = (Objects.requireNonNull(DatabaseConfig.class.getClassLoader().getResource("config.properties")).getFile()).replaceAll("%20", " ");
    private static final Logger logger = LogManager.getLogger();

    private static Properties getProperties() throws RuntimeException
    {
        logger.traceEntry();

        Properties properties = new Properties();
        try
        {
            properties.load(new FileReader(CONFIG_LOCATION));
        }
        catch (IOException exception)
        {
            logger.error(exception);
            exception.printStackTrace();
            throw new RuntimeException("Error while reading the config file: " + CONFIG_LOCATION);
        }

        logger.traceExit(properties);
        return properties;
    }

    public static String getProperty(String Key) throws RuntimeException
    {
        return getProperties().getProperty(Key);
    }
}
