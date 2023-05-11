package moto.rest.client;

import moto.Motorcycle;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.web.client.RestTemplate;

import java.util.concurrent.Callable;

public class MotoClient
{
    public static final String URL = "http://localhost:8080/moto/motorcycles";

    private RestTemplate restTemplate = new RestTemplate();

    private <T> T execute(Callable<T> callable)
    {
        try
        {
            return callable.call();
        }
        catch (Exception exception)
        {
            exception.printStackTrace();
        }

        return null;
    }

    public Motorcycle[] findAll()
    {
        return execute(() -> this.restTemplate.getForObject(URL, Motorcycle[].class));
    }

    public Motorcycle find(Integer id)
    {
        return execute(() -> this.restTemplate.getForObject(String.format("%s/%d", URL, id), Motorcycle.class));
    }

    public Motorcycle save(Motorcycle motorcycle)
    {
        return execute(() ->
        {
            Motorcycle newMotorcycle = this.restTemplate.postForObject(URL, motorcycle, Motorcycle.class);
            motorcycle.setId(newMotorcycle.getId());
            return motorcycle;
        });
    }

    public Motorcycle update(Motorcycle motorcycle)
    {
        return execute(() -> this.restTemplate.exchange(URL, HttpMethod.PUT, new HttpEntity<Motorcycle>(motorcycle), Motorcycle.class)).getBody();
    }

    public void remove(Integer id)
    {
        execute(() ->
        {
            this.restTemplate.delete(String.format("%s/%d", URL, id));
            return null;
        });
    }
}