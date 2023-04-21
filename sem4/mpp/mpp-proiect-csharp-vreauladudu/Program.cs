using mpp_proiect_csharp_vreauladudu.repository.database;
using mpp_proiect_csharp_vreauladudu.repository;
using System;
using System.Windows.Forms;
using mpp_proiect_csharp_vreauladudu.service;
using networking;

namespace mpp_proiect_csharp_vreauladudu
{
    internal static class Program
    {
        [STAThread]
        static void Main()
        {
            IMotoService server = new MotoServerObjectProxy("127.0.0.1", 55555);
            MotoClientController controller = new MotoClientController(server);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new LoginWindow(controller));
        }
    }
}