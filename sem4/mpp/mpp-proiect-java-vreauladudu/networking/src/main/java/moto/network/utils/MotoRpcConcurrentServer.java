package moto.network.utils;

import moto.network.rpcprotocol.MotoClientRpcReflectionWorker;
import moto.services.IMotoService;

import java.net.Socket;

public class MotoRpcConcurrentServer extends AbstractConcurrentServer
{
    private IMotoService motoServer;

    public MotoRpcConcurrentServer(int port, IMotoService motoServer)
    {
        super(port);
        this.motoServer = motoServer;
        System.out.println("Moto - MotoRpcConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client)
    {
        MotoClientRpcReflectionWorker worker = new MotoClientRpcReflectionWorker(motoServer, client);

        Thread th = new Thread(worker);
        return th;
    }

    @Override
    public void stop()
    {
        System.out.println("Stopping services ...");
    }
}