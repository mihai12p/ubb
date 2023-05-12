package moto.rest.client;

import moto.Motorcycle;

import java.util.Arrays;

public class RestClient
{
    private final static MotoClient motoClient = new MotoClient();

    public static void main(String[] args)
    {
        Motorcycle motorcycle = new Motorcycle();
        motorcycle.setBrand("HondaTESTREST_Java");
        motorcycle.setCapacity(125);

        show(() -> System.out.println(motoClient.save(motorcycle)));
        show(() -> Arrays.stream(motoClient.findAll()).toList().forEach(System.out::println));
        show(() -> System.out.println(motoClient.find(8)));
        show(() ->
        {
            motorcycle.setBrand("MOTOUPDATE");
            System.out.println(motoClient.update(motorcycle));
        });
        show(() -> motoClient.remove(8));
    }

    private static void show(Runnable task)
    {
        task.run();
    }
}