package moto.network.utils;

import java.net.Socket;

public abstract class AbstractConcurrentServer extends AbstractServer
{
    public AbstractConcurrentServer(int port)
    {
        super(port);
        System.out.println("Concurrent AbstractServer");
    }

    @Override
    protected void processRequest(Socket client)
    {
        Thread th = this.createWorker(client);
        th.start();
    }

    protected abstract Thread createWorker(Socket client);
}