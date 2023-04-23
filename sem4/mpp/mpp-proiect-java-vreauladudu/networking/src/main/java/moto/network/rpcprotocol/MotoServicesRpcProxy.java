package moto.network.rpcprotocol;

import moto.Motorcycle;
import moto.Participant;
import moto.User;
import moto.services.IMotoObserver;
import moto.services.IMotoService;
import moto.services.MotoException;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.List;
import java.util.Map;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class MotoServicesRpcProxy implements IMotoService
{
    private final String host;
    private final Integer port;

    private IMotoObserver client;

    private ObjectInputStream inputStream;
    private ObjectOutputStream outputStream;
    private Socket connection;

    private final BlockingQueue<Response> Responses;
    private volatile boolean isFinished;

    public MotoServicesRpcProxy(String host, Integer port)
    {
        this.host = host;
        this.port = port;
        this.Responses = new LinkedBlockingDeque<>();
    }

    private boolean isUpdate(Response response)
    {
        return response.type() == ResponseType.PARTICIPANT_ADDED;
    }

    private class ReaderThread implements Runnable
    {
        public void run()
        {
            while (!isFinished)
            {
                try
                {
                    Object response = inputStream.readObject();
                    System.out.println("response received " + response);
                    if (isUpdate((Response)response))
                    {
                        handleUpdate((Response)response);
                    }
                    else
                    {
                        try
                        {
                            Responses.put((Response)response);
                        }
                        catch (InterruptedException exception)
                        {
                            exception.printStackTrace();
                        }
                    }
                }
                catch (IOException | ClassNotFoundException exception)
                {
                    System.out.println("Reading error " + exception);
                }
            }
        }
    }

    private void handleUpdate(Response response)
    {
        if (response.type() == ResponseType.PARTICIPANT_ADDED)
        {
            Participant participant = (Participant)response.data();
            System.out.println("Participant added " + participant);
            try
            {
                this.client.participantAdded(participant);
            }
            catch (MotoException exception)
            {
                exception.printStackTrace();
            }
        }
    }

    private void startReader()
    {
        Thread th = new Thread(new ReaderThread());
        th.start();
    }

    private void sendRequest(Request request) throws MotoException
    {
        try
        {
            this.outputStream.writeObject(request);
            this.outputStream.flush();
        }
        catch (IOException exception)
        {
            throw new MotoException("Error sending object " + exception);
        }
    }

    private Response readResponse() throws MotoException
    {
        Response response = null;
        try
        {
            response = this.Responses.take();
        }
        catch (InterruptedException exception)
        {
            exception.printStackTrace();
        }
        return response;
    }

    private void initializeConnection() throws MotoException
    {
        try
        {
            this.connection = new Socket(this.host, this.port);

            this.outputStream = new ObjectOutputStream(this.connection.getOutputStream());
            this.outputStream.flush();

            this.inputStream = new ObjectInputStream(this.connection.getInputStream());

            this.isFinished = false;
            this.startReader();
        }
        catch (IOException exception)
        {
            exception.printStackTrace();
        }
    }

    private void closeConnection()
    {
        this.isFinished = true;
        try
        {
            this.inputStream.close();
            this.outputStream.close();
            this.connection.close();
            this.client = null;
        }
        catch (IOException exception)
        {
            exception.printStackTrace();
        }
    }

    public void login(User user, IMotoObserver client) throws MotoException
    {
        this.initializeConnection();
        Request request = new Request.Builder().type(RequestType.LOGIN).data(user).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        if (response.type() == ResponseType.OK)
        {
            this.client = client;
        }
        else if (response.type() == ResponseType.ERROR)
        {
            this.closeConnection();
            throw new MotoException(response.data().toString());
        }
    }

    public void logout(User user, IMotoObserver client) throws MotoException
    {
        Request request = new Request.Builder().type(RequestType.LOGOUT).data(user).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        this.closeConnection();
        if (response.type() == ResponseType.ERROR)
        {
            throw new MotoException(response.data().toString());
        }
    }

    @SuppressWarnings("unchecked")
    public Map<Integer, List<Motorcycle>> listRaces(IMotoObserver client) throws MotoException
    {
        Request request = new Request.Builder().type(RequestType.LIST_RACES).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        if (response.type() == ResponseType.ERROR)
        {
            throw new MotoException(response.data().toString());
        }

        return (Map<Integer, List<Motorcycle>>)response.data();
    }

    @SuppressWarnings("unchecked")
    public Iterable<Motorcycle> listMotorcycles(IMotoObserver client) throws MotoException
    {
        Request request = new Request.Builder().type(RequestType.LIST_MOTORCYCLES).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        if (response.type() == ResponseType.ERROR)
        {
            throw new MotoException(response.data().toString());
        }

        return (Iterable<Motorcycle>)response.data();
    }

    @SuppressWarnings("unchecked")
    public List<Motorcycle> listMotorcyclesByCapacity(Integer capacity, IMotoObserver client) throws MotoException
    {
        Request request = new Request.Builder().type(RequestType.LIST_MOTORCYCLES_BY_CAPACITY).data(capacity).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        if (response.type() == ResponseType.ERROR)
        {
            throw new MotoException(response.data().toString());
        }

        return (List<Motorcycle>)response.data();
    }

    @SuppressWarnings("unchecked")
    public List<Participant> findParticipantForRace(Integer motorcycleId, IMotoObserver client) throws MotoException
    {
        Request request = new Request.Builder().type(RequestType.FIND_PARTICIPANTS).data(motorcycleId).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        if (response.type() == ResponseType.ERROR)
        {
            throw new MotoException(response.data().toString());
        }

        return (List<Participant>)response.data();
    }

    @SuppressWarnings("unchecked")
    public List<Motorcycle> listMotorcyclesByBrand(String brand, IMotoObserver client) throws MotoException
    {
        Request request = new Request.Builder().type(RequestType.LIST_MOTORCYCLES_BY_BRAND).data(brand).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        if (response.type() == ResponseType.ERROR)
        {
            throw new MotoException(response.data().toString());
        }

        return (List<Motorcycle>)response.data();
    }

    public Motorcycle findMotorcycleById(Integer motorcycleId, IMotoObserver client) throws MotoException
    {
        Request request = new Request.Builder().type(RequestType.FIND_MOTORCYCLE).data(motorcycleId).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        if (response.type() == ResponseType.ERROR)
        {
            throw new MotoException(response.data().toString());
        }

        return (Motorcycle)response.data();
    }

    public void addParticipant(String participantName, String motorcycleBrand, Integer motorcycleCapacity, IMotoObserver client) throws MotoException
    {
        Object[] objects = { participantName, motorcycleBrand, motorcycleCapacity };
        Request request = new Request.Builder().type(RequestType.ADD_PARTICIPANT).data(objects).build();
        this.sendRequest(request);
        Response response = this.readResponse();
        if (response.type() == ResponseType.ERROR)
        {
            throw new MotoException(response.data().toString());
        }
    }
}