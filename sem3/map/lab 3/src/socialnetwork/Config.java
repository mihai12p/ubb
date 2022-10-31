package socialnetwork;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

/**
 * {@code Config} is the class that manages the resources.
 */
public class Config
{
    public static final String CONFIG_LOCATION = (Config.class.getClassLoader().getResource("resources/config.properties").getFile()).replaceAll("%20", " ");
    public static Properties getProperties()
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
}
