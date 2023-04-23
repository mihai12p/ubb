package moto.network.rpcprotocol;

import moto.Motorcycle;
import moto.Participant;
import moto.User;
import moto.services.IMotoObserver;
import moto.services.IMotoService;
import moto.services.MotoException;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.util.List;
import java.util.Map;

public class MotoClientRpcReflectionWorker implements Runnable, IMotoObserver
{
    private IMotoService server;
    private Socket connection;

    private ObjectInputStream inputStream;
    private ObjectOutput outputStream;
    private volatile boolean isConnected;

    public MotoClientRpcReflectionWorker(IMotoService server, Socket connection)
    {
        this.server = server;
        this.connection = connection;

        try
        {
            this.outputStream = new ObjectOutputStream(this.connection.getOutputStream());
            this.outputStream.flush();

            this.inputStream = new ObjectInputStream(this.connection.getInputStream());

            this.isConnected = true;
        }
        catch (IOException exception)
        {
            exception.printStackTrace();
        }
    }

    private Response handleRequest(Request request)
    {
        Response response = null;
        String handlerName = "handle" + request.type();
        System.out.println("HandlerName " + handlerName);
        try
        {
            Method method = this.getClass().getDeclaredMethod(handlerName, Request.class);
            response = (Response) method.invoke(this, request);
            System.out.println("Method " + handlerName + " invoked");
        }
        catch (NoSuchMethodException | InvocationTargetException | IllegalAccessException exception)
        {
            exception.printStackTrace();
        }

        return response;
    }

    private void sendResponse(Response response) throws IOException
    {
        System.out.println("sending response " + response);
        this.outputStream.writeObject(response);
        this.outputStream.flush();
    }

    public void run()
    {
        while (this.isConnected)
        {
            try
            {
                Object request = this.inputStream.readObject();
                Response response = this.handleRequest((Request)request);
                if (response != null)
                {
                    this.sendResponse(response);
                }
            }
            catch (IOException | ClassNotFoundException exception)
            {
                exception.printStackTrace();
            }

            try
            {
                Thread.sleep(100);
            }
            catch (InterruptedException exception)
            {
                exception.printStackTrace();
            }
        }

        try
        {
            this.inputStream.close();
            this.outputStream.close();
            this.connection.close();
        }
        catch (IOException exception)
        {
            exception.printStackTrace();
        }
    }

    public void participantAdded(Participant participant)
    {
        Response response = new Response.Builder().type(ResponseType.PARTICIPANT_ADDED).data(participant).build();
        System.out.println("Participant added1 " + participant);
        try
        {
            this.sendResponse(response);
        }
        catch (IOException exception)
        {
            exception.printStackTrace();
        }
    }

    private static Response OkResponse = new Response.Builder().type(ResponseType.OK).build();

    private Response handleLOGIN(Request request)
    {
        System.out.println("Login request..." + request.type());
        User user = (User)request.data();
        try
        {
            this.server.login(user, this);
            return OkResponse;
        }
        catch (MotoException exception)
        {
            this.isConnected = false;
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }

    private Response handleLOGOUT(Request request)
    {
        System.out.println("Logout request...");
        User user = (User)request.data();
        try
        {
            this.server.logout(user, this);
            this.isConnected = false;
            return OkResponse;
        }
        catch (MotoException exception)
        {
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }

    private Response handleLIST_RACES(Request request)
    {
        System.out.println("ListRaces request...");
        try
        {
            Map<Integer, List<Motorcycle>> races = null;
            races = this.server.listRaces(this);
            return new Response.Builder().type(ResponseType.LIST_RACES).data(races).build();
        }
        catch (MotoException exception)
        {
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }

    private Response handleLIST_MOTORCYCLES(Request request)
    {
        System.out.println("ListMotorcycles request...");
        try
        {
            Iterable<Motorcycle> motorcycles = null;
            motorcycles = this.server.listMotorcycles(this);
            return new Response.Builder().type(ResponseType.LIST_MOTORCYCLES).data(motorcycles).build();
        }
        catch (MotoException exception)
        {
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }

    private Response handleLIST_MOTORCYCLES_BY_CAPACITY(Request request)
    {
        System.out.println("ListMotorcycles request...");
        try
        {
            List<Motorcycle> motorcycles = null;
            motorcycles = this.server.listMotorcyclesByCapacity((Integer)request.data(), this);
            return new Response.Builder().type(ResponseType.LIST_MOTORCYCLES).data(motorcycles).build();
        }
        catch (MotoException exception)
        {
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }

    private Response handleFIND_PARTICIPANTS(Request request)
    {
        System.out.println("FindParticipants request...");
        try
        {
            List<Participant> participants = null;
            participants = this.server.findParticipantForRace((Integer)request.data(), this);
            return new Response.Builder().type(ResponseType.FIND_PARTICIPANTS).data(participants).build();
        }
        catch (MotoException exception)
        {
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }

    private Response handleLIST_MOTORCYCLES_BY_BRAND(Request request)
    {
        System.out.println("ListMotorcycles request...");
        try
        {
            List<Motorcycle> motorcycles = null;
            motorcycles = this.server.listMotorcyclesByBrand((String)request.data(), this);
            return new Response.Builder().type(ResponseType.LIST_MOTORCYCLES).data(motorcycles).build();
        }
        catch (MotoException exception)
        {
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }

    private Response handleFIND_MOTORCYCLE(Request request)
    {
        System.out.println("FindMotorcycle request...");
        try
        {
            Motorcycle motorcycle = null;
            motorcycle = this.server.findMotorcycleById((Integer)request.data(), this);
            return new Response.Builder().type(ResponseType.MOTORCYCLE).data(motorcycle).build();
        }
        catch (MotoException exception)
        {
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }

    private Response handleADD_PARTICIPANT(Request request)
    {
        System.out.println("Add participant request...");
        try
        {
            Object[] objects = (Object[])request.data();
            this.server.addParticipant((String)objects[0], (String)objects[1], (Integer)objects[2], this);
            return new Response.Builder().type(ResponseType.PARTICIPANT).build();
        }
        catch (MotoException exception)
        {
            return new Response.Builder().type(ResponseType.ERROR).data(exception.getMessage()).build();
        }
    }
}