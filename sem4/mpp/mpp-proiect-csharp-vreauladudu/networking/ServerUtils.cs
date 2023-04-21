using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace ServerTemplate
{
    public abstract class AbstractServer
    {
        private TcpListener Server;
        private String Host;
        private int Port;

        public AbstractServer(String host, int port)
        {
            this.Host = host;
            this.Port = port;
        }

        public void Start()
        {
            IPAddress addr = IPAddress.Parse(this.Host);
            IPEndPoint ep = new IPEndPoint(addr, this.Port);
            this.Server = new TcpListener(ep);
            this.Server.Start();

            while (true)
            {
                Console.WriteLine("Waiting for clients ...");
                TcpClient client = this.Server.AcceptTcpClient();
                Console.WriteLine("Client connected ...");
                processRequest(client);
            }
        }

        public abstract void processRequest(TcpClient client);
    }

    public abstract class ConcurrentServer : AbstractServer
    {
        public ConcurrentServer(string host, int port) : base(host, port) { }

        public override void processRequest(TcpClient client)
        {
            Thread th = createWorker(client);
            th.Start();
        }

        protected abstract Thread createWorker(TcpClient client);
    }
}