using lab_8.service;

namespace lab_8.ui
{
    internal class Consola
    {
        private Service _service;

        public Consola(Service service)
        {
            _service = service;
        }

        private void jucatoriByEchipaUI()
        {
            Console.Write("Echipa: ");
            _service.getJucatoriByEchipa(Console.ReadLine());
        }

        private void jucatoriActiviByMeciUI()
        {
            Console.Write("Echipa1: ");
            string? echipa1 = Console.ReadLine();

            Console.Write("Echipa2: ");
            string? echipa2 = Console.ReadLine();

            Console.Write("Data: ");
            DateTime data;
            bool eValidaData = DateTime.TryParse(Console.ReadLine(), out data);
            if (!eValidaData)
            {
                Console.WriteLine("Data invalida");
                return;
            }

            _service.getJucatoriActiviByMeci(echipa1, echipa2, data);
        }

        private void meciuriByPerioadaUI()
        {
            Console.Write("Data start: ");
            DateTime dataStart;
            bool eValidaData = DateTime.TryParse(Console.ReadLine(), out dataStart);
            if (!eValidaData)
            {
                Console.WriteLine("Data start invalida");
                return;
            }

            Console.Write("Data sfarsit: ");
            DateTime dataSfarsit;
            eValidaData = DateTime.TryParse(Console.ReadLine(), out dataSfarsit);
            if (!eValidaData)
            {
                Console.WriteLine("Data sfarsit invalida");
                return;
            }

            _service.getMeciuriByPerioada(dataStart, dataSfarsit);
        }

        private void scorByMeciUI()
        {
            Console.Write("Echipa1: ");
            string? echipa1 = Console.ReadLine();

            Console.Write("Echipa2: ");
            string? echipa2 = Console.ReadLine();

            Console.Write("Data: ");
            DateTime data;
            bool eValidaData = DateTime.TryParse(Console.ReadLine(), out data);
            if (!eValidaData)
            {
                Console.WriteLine("Data invalida");
                return;
            }

            _service.getScoreByMeci(echipa1, echipa2, data);
        }

        public void start()
        {
            bool finished = false;
            while (!finished)
            {
                Console.WriteLine("Meniu: \n\t1 - afiseaza jucatorii unei echipe" +
                    "\n\t2 - afiseaza jucatorii activi ai unei echipe de la un anumit meci" +
                    "\n\t3 - afiseaza toate meciurile dintr-o anumita perioada" +
                    "\n\t4 - afiseaza scorul de la un anumit meci" +
                    "\n\t5 - exit\n>>> ");

                int optiune;
                bool eValidaOptiunea = int.TryParse(Console.ReadLine(), out optiune);
                
                if (eValidaOptiunea)
                {
                    try
                    {
                        switch (optiune)
                        {
                            case 1:
                            {
                                jucatoriByEchipaUI(); // Boston Celtics
                                break;
                            }
                            case 2:
                            {
                                jucatoriActiviByMeciUI(); // "Boston Celtics" "Washington Wizards" "2023-08-08 14:20:00"
                                break;
                            }
                            case 3:
                            {
                                meciuriByPerioadaUI(); // "2023-01-08 14:20:00" "2023-08-08 14:20:00"
                                break;
                            }
                            case 4:
                            {
                                scorByMeciUI(); // "Boston Celtics" "Washington Wizards" "2023-08-08 14:20:00"
                                break;
                            }
                            case 5:
                            {
                                finished = true;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e);
                    }
                }
            }
        }
    }
}