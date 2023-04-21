using ServerTemplate;
using System.Net.Sockets;
using networking;
using mpp_proiect_csharp_vreauladudu.service;
using mpp_proiect_csharp_vreauladudu.repository.database;
using mpp_proiect_csharp_vreauladudu.repository;
using Server.Impl;

namespace Server
{
    public class SerialMotoServer : ConcurrentServer
    {
        private IMotoService Server;
        private MotoClientObjectWorker? Worker;

        public SerialMotoServer(string host, int port, IMotoService server) : base(host, port)
        {
            this.Server = server;
            Console.WriteLine("SerialMotoServer...");
        }

        protected override Thread createWorker(TcpClient client)
        {
            this.Worker = new MotoClientObjectWorker(this.Server, client);
            return new Thread(new ThreadStart(this.Worker.run));
        }
    }

    class Server
    {
        static void Main(string[] args)
        {
            MotorcycleRepository motorcycles = new MotorcycleDatabase();
            ParticipantRepository participants = new ParticipantDatabase();
            UserRepository users = new UserDatabase();
            IMotoService service = new MotoServer(motorcycles, participants, users);

            SerialMotoServer server = new SerialMotoServer("127.0.0.1", 55555, service);
            server.Start();
            Console.WriteLine("Server started...");
            Console.ReadLine();
        }
    }
}