using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Threading;
using mpp_proiect_csharp_vreauladudu.domain;
using mpp_proiect_csharp_vreauladudu.service;
using services;

namespace networking
{
    public class MotoServerObjectProxy : IMotoService
    {
        private string Host;
        private int Port;

        private IMotoObserver Client;

        private NetworkStream NetStream;

        private IFormatter Formatter;
        private TcpClient Connection;

        private Queue<Response> Responses;
        private volatile bool IsFinished;
        private EventWaitHandle WaitHandle;

        public MotoServerObjectProxy(string host, int port)
        {
            this.Host = host;
            this.Port = port;
            this.Responses = new Queue<Response>();
        }

        public virtual void run()
        {
            while (!this.IsFinished)
            {
                try
                {
                    object response = this.Formatter.Deserialize(this.NetStream);
                    Console.WriteLine("response received " + response);
                    if (response is UpdateResponse)
                    {
                        handleUpdate((UpdateResponse)response);
                    }
                    else
                    {
                        lock (this.Responses)
                        {
                            this.Responses.Enqueue((Response)response);
                        }
                        this.WaitHandle.Set();
                    }
                }
                catch (Exception exception)
                {
                    Console.Write(exception.StackTrace);
                }
            }
        }

        private void handleUpdate(UpdateResponse response)
        {
            if (response is ParticipantAddedResponse)
            {
                ParticipantAddedResponse participantAdded = (ParticipantAddedResponse)response;
                try
                {
                    this.Client.participantAdded(participantAdded.Participant);
                }
                catch (Exception exception)
                {
                    Console.Write(exception.StackTrace);
                }
            }
        }

        private void startReader()
        {
            Thread th = new Thread(this.run);
            th.Start();
        }

        private void sendRequest(Request request)
        {
            try
            {
                this.Formatter.Serialize(this.NetStream, request);
                this.NetStream.Flush();
            }
            catch (Exception exception)
            {
                Console.Write(exception.StackTrace);
            }
        }

        private Response readResponse()
        {
            Response response = null;
            try
            {
                this.WaitHandle.WaitOne();
                lock (this.Responses)
                {
                    response = this.Responses.Dequeue();
                }
            }
            catch (Exception exception)
            {
                Console.Write(exception.StackTrace);
            }

            return response;
        }

        private void initializeConnection()
        {
            try
            {
                this.Connection = new TcpClient(this.Host, this.Port);
                this.NetStream = this.Connection.GetStream();
                this.Formatter = new BinaryFormatter();
                this.IsFinished = false;
                this.WaitHandle = new AutoResetEvent(false);
                this.startReader();
            }
            catch (Exception exception)
            {
                Console.Write(exception.StackTrace);
            }
        }

        private void closeConnection()
        {
            this.IsFinished = true;
            try
            {
                this.NetStream.Close();
                this.Connection.Close();
                this.WaitHandle.Close();
                this.Client = null;
            }
            catch (Exception exception)
            {
                Console.Write(exception.StackTrace);
            }
        }

        public virtual void login(User user, IMotoObserver client)
        {
            this.initializeConnection();
            this.sendRequest(new LoginRequest(user));
            Response response = readResponse();
            if (response is OkResponse)
            {
                this.Client = client;
                return;
            }
            else if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                this.closeConnection();
                throw new MotoException(error.Message);
            }
        }

        public virtual void logout(User user, IMotoObserver client)
        {
            this.sendRequest(new LogoutRequest(user));
            Response response = readResponse();
            this.closeConnection();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new MotoException(error.Message);
            }
        }

        public virtual Dictionary<int, List<Motorcycle>> listRaces(IMotoObserver client)
        {
            this.sendRequest(new ListRacesRequest());
            Response response = readResponse();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new MotoException(error.Message);
            }

            ListRacesResponse racesResponse = (ListRacesResponse)response;
            return racesResponse.Races;
        }

        public virtual IEnumerable<Motorcycle> listMotorcycles(IMotoObserver client)
        {
            this.sendRequest(new ListMotorcyclesRequest());
            Response response = readResponse();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new MotoException(error.Message);
            }

            ListMotorcyclesResponse motorcyclesResponse = (ListMotorcyclesResponse)response;
            return motorcyclesResponse.Motorcycles;
        }

        public virtual List<Motorcycle> listMotorcyclesByCapacity(int capacity, IMotoObserver client)
        {
            this.sendRequest(new ListMotorcyclesByCapacityRequest(capacity));
            Response response = readResponse();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new MotoException(error.Message);
            }

            ListMotorcyclesResponse motorcyclesResponse = (ListMotorcyclesResponse)response;
            return motorcyclesResponse.MotorcyclesList;
        }

        public virtual List<Participant> findParticipantForRace(int motorcycleId, IMotoObserver client)
        {
            this.sendRequest(new FindParticipantsRequest(motorcycleId));
            Response response = readResponse();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new MotoException(error.Message);
            }

            FindParticipantsResponse participantResponse = (FindParticipantsResponse)response;
            return participantResponse.Participants;
        }

        public virtual List<Motorcycle> listMotorcyclesByBrand(String brand, IMotoObserver client)
        {
            this.sendRequest(new ListMotorcyclesByBrandRequest(brand));
            Response response = readResponse();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new MotoException(error.Message);
            }

            ListMotorcyclesResponse motorcyclesResponse = (ListMotorcyclesResponse)response;
            return motorcyclesResponse.MotorcyclesList;
        }
        
        public virtual Motorcycle findMotorcycleById(int motorcycleId, IMotoObserver client)
        {
            this.sendRequest(new FindMotorcycleRequest(motorcycleId));
            Response response = readResponse();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new MotoException(error.Message);
            }

            MotorcycleResponse motorcyclesResponse = (MotorcycleResponse)response;
            return motorcyclesResponse.Motorcycle;
        }

        public virtual void addParticipant(String participantName, String motorcycleBrand, int motorcycleCapacity, IMotoObserver client)
        {
            this.sendRequest(new AddParticipantRequest(participantName, motorcycleBrand, motorcycleCapacity));
            Response response = readResponse();
            if (response is ErrorResponse)
            {
                ErrorResponse error = (ErrorResponse)response;
                throw new MotoException(error.Message);
            }
        }
    }
}