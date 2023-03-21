package moto;

import moto.service.Service;

public class Main
{
    public static void main(String[] args)
    {
        Service service = new Service();
        service.listMotorcycles();
        service.listParticipants();
        service.listUsers();
    }
}