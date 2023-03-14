package moto.configuration;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class DatabaseConfig
{
    public static final String CONFIG_LOCATION = (DatabaseConfig.class.getClassLoader().getResource("moto/config.properties").getFile()).replaceAll("%20", " ");

    private static Properties getProperties() throws RuntimeException
    {
        Properties properties = new Properties();
        try
        {
            properties.load(new FileReader(CONFIG_LOCATION));
        }
        catch (IOException exception)
        {
            exception.printStackTrace();
            throw new RuntimeException("Error while reading the config file: " + CONFIG_LOCATION);
        }

        return properties;
    }

    public static String getProperty(String Key) throws RuntimeException
    {
        return getProperties().getProperty(Key);
    }
}
