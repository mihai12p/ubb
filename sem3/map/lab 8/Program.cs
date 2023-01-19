using lab_8.service;
using lab_8.ui;

namespace lab_8;
class Program
{
    static void Main(string[] args)
    {
        Consola console = new Consola(new Service());
        console.start();
    }
}