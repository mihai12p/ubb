package socialnetwork;

import socialnetwork.service.Service;
import socialnetwork.ui.Console;

public class Main
{
    public static void main(String[] args)
    {
        Service service = new Service();
        Console console = new Console(service);
        console.start();
    }
}