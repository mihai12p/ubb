using mpp_proiect_csharp_vreauladudu.domain;
using mpp_proiect_csharp_vreauladudu.service;
using services;
using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Threading;

namespace networking
{
    public class MotoClientObjectWorker : IMotoObserver
    {
        private IMotoService Server;
        private TcpClient Connection;

        private NetworkStream NetStream;
        private IFormatter Formatter;
        private volatile bool IsConnected;

        public MotoClientObjectWorker(IMotoService server, TcpClient connection)
        {
            this.Server = server;
            this.Connection = connection;

            try
            {
                this.NetStream = connection.GetStream();
                this.Formatter = new BinaryFormatter();
                this.IsConnected = true;
            }
            catch (Exception exception)
            {
                Console.Write(exception.StackTrace);
            }
        }

        private Response handleRequest(Request request)
        {
            if (request is LoginRequest)
            {
                Console.WriteLine("Login request...");
                LoginRequest loginRequest = (LoginRequest) request;
                User user = loginRequest.User;
                try
                {
                    lock (this.Server)
                    {
                        this.Server.login(user, this);
                    }
                    return new OkResponse();
                }
                catch (MotoException exception)
                {
                    this.IsConnected = false;
                    return new ErrorResponse(exception.Message);
                }
            }
            else if (request is LogoutRequest)
            {
                Console.WriteLine("Logout request...");
                LogoutRequest logoutRequest = (LogoutRequest) request;
                User user = logoutRequest.User;
                try
                {
                    lock (this.Server)
                    {
                        this.Server.logout(user, this);
                    }
                    this.IsConnected = false;
                    return new OkResponse();
                }
                catch (MotoException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }
            else if (request is ListRacesRequest)
            {
                Console.WriteLine("ListRaces request...");
                try
                {
                    Dictionary<int, List<Motorcycle>> races = null;
                    lock (this.Server)
                    {
                        races = this.Server.listRaces(this);
                    }
                    return new ListRacesResponse(races);
                }
                catch (MotoException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }
            else if (request is ListMotorcyclesRequest)
            {
                Console.WriteLine("ListMotorcycles request...");
                try
                {
                    IEnumerable<Motorcycle> motorcycles = null;
                    lock (this.Server)
                    {
                        motorcycles = this.Server.listMotorcycles(this);
                    }
                    return new ListMotorcyclesResponse(motorcycles);
                }
                catch (MotoException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }
            else if (request is ListMotorcyclesByCapacityRequest)
            {
                Console.WriteLine("ListMotorcycles request...");
                ListMotorcyclesByCapacityRequest listMotorcyclesRequest = (ListMotorcyclesByCapacityRequest) request;
                try
                {
                    List<Motorcycle> motorcycles = null;
                    lock (this.Server)
                    {
                        motorcycles = this.Server.listMotorcyclesByCapacity(listMotorcyclesRequest.Capacity, this);
                    }
                    return new ListMotorcyclesResponse(motorcycles);
                }
                catch (MotoException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }
            else if (request is FindParticipantsRequest)
            {
                Console.WriteLine("FindParticipants request...");
                FindParticipantsRequest listParticipants = (FindParticipantsRequest)request;
                try
                {
                    List<Participant> participants = null;
                    lock (this.Server)
                    {
                        participants = this.Server.findParticipantForRace(listParticipants.MotorcycleId, this);
                    }
                    return new FindParticipantsResponse(participants);
                }
                catch (MotoException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }
            else if (request is ListMotorcyclesByBrandRequest)
            {
                Console.WriteLine("ListMotorcycles request...");
                ListMotorcyclesByBrandRequest listMotorcyclesRequest = (ListMotorcyclesByBrandRequest)request;
                try
                {
                    List<Motorcycle> motorcycles = null;
                    lock (this.Server)
                    {
                        motorcycles = this.Server.listMotorcyclesByBrand(listMotorcyclesRequest.Brand, this);
                    }
                    return new ListMotorcyclesResponse(motorcycles);
                }
                catch (MotoException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }
            else if (request is FindMotorcycleRequest)
            {
                Console.WriteLine("FindMotorcycle request...");
                FindMotorcycleRequest motorcycleRequest = (FindMotorcycleRequest)request;
                try
                {
                    Motorcycle motorcycle = null;
                    lock (this.Server)
                    {
                        motorcycle = this.Server.findMotorcycleById(motorcycleRequest.MotorcycleId, this);
                    }
                    return new MotorcycleResponse(motorcycle);
                }
                catch (MotoException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }
            else if (request is AddParticipantRequest)
            {
                Console.WriteLine("Add participant request...");
                AddParticipantRequest addParticipant = (AddParticipantRequest) request;
                String participantName = addParticipant.ParticipantName;
                String motorcycleBrand = addParticipant.MotorcycleBrand;
                int motorcycleCapacity = addParticipant.MotorcycleCapacity;
                try
                {
                    lock (this.Server)
                    {
                        this.Server.addParticipant(participantName, motorcycleBrand, motorcycleCapacity, this);
                    }
                    return new ParticipantResponse();
                }
                catch (MotoException exception)
                {
                    return new ErrorResponse(exception.Message);
                }
            }
            return null;
        }

        private void sendResponse(Response response)
        {
            Console.WriteLine("sending response " + response);
            lock (this.NetStream)
            {
                this.Formatter.Serialize(this.NetStream, response);
                this.NetStream.Flush();
            }
        }

        public virtual void run()
        {
            while (this.IsConnected)
            {
                try
                {
                    object request = this.Formatter.Deserialize(this.NetStream);
                    object response = handleRequest((Request)request);
                    if (response != null)
                    {
                        sendResponse((Response)response);
                    }
                }
                catch (Exception exception)
                {
                    Console.Write(exception.StackTrace);
                }

                try
                {
                    Thread.Sleep(100);
                }
                catch (Exception exception)
                {
                    Console.Write(exception.StackTrace);
                }
            }

            try
            {
                this.NetStream.Close();
                this.Connection.Close();
            }
            catch (Exception exception)
            {
                Console.Write(exception.StackTrace);
            }
        }

        public virtual void participantAdded(Participant participant)
        {
            try
            {
                sendResponse(new ParticipantAddedResponse(participant));
            }
            catch (Exception exception)
            {
                Console.Write(exception.StackTrace);
            }
        }
    }
}