package moto;

import moto.network.utils.AbstractServer;
import moto.network.utils.MotoRpcConcurrentServer;
import moto.network.utils.ServerException;
import moto.repository.MotorcycleRepository;
import moto.repository.ParticipantRepository;
import moto.repository.UserRepository;
import moto.repository.database.MotorcycleDatabase;
import moto.repository.database.ParticipantDatabase;
import moto.repository.database.UserDatabase;
import moto.repository.hibernate.HibernateUtils;
import moto.repository.hibernate.UserHibernate;
import moto.server.MotoServer;
import moto.services.IMotoService;

import java.io.IOException;
import java.util.Properties;

public class RpcServer
{
    public static void main(String[] args)
    {
        Properties serverProperties = new Properties();
        try
        {
            serverProperties.load(RpcServer.class.getResourceAsStream("/motoserver.properties"));
            System.out.println("Server properties set.");
            serverProperties.list(System.out);
        }
        catch (IOException exception)
        {
            System.err.println("Cannot find motoserver.properties " + exception);
            return;
        }

        MotorcycleRepository motorcycles = new MotorcycleDatabase(serverProperties);
        ParticipantRepository participants = new ParticipantDatabase(serverProperties);
        UserRepository users = new UserHibernate();
        IMotoService service = new MotoServer(motorcycles, participants, users);

        AbstractServer server = new MotoRpcConcurrentServer(Integer.parseInt(serverProperties.getProperty("server.port")), service);
        try
        {
            server.start();
        }
        catch (ServerException exception)
        {
            System.err.println("Error starting the server " + exception.getCause());
        }
        finally
        {
            try
            {
                HibernateUtils.close();
                server.stop();
            }
            catch (ServerException exception)
            {
                System.err.println("Error stopping the server " + exception.getMessage());
            }
        }
    }
}