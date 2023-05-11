package moto;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import java.io.IOException;
import java.util.Properties;

@SpringBootApplication
public class RestServices
{
    public static void main(String[] args)
    {
        SpringApplication.run(RestServices.class, args);
    }

    @Bean(name = "properties")
    public static Properties getProperties()
    {
        Properties properties = new Properties();
        try
        {
            properties.load(RestServices.class.getResourceAsStream("/restservices.properties"));
        }
        catch (IOException exception)
        {
            System.err.println("Cannot find restservices.properties " + exception);
        }

        return properties;
    }
}