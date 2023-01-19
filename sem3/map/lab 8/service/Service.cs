using lab_8.domain;
using lab_8.repository;
using lab_8.repository.file;

namespace lab_8.service
{
    internal class Service
    {
        private Repository<int, Echipa> _echipe;
        private Repository<int, Elev> _elevi;
        private Repository<int, Meci> _meciuri;
        private Repository<int, JucatorActiv> _jucatori;

        public Service()
        {
            _echipe = new EchipaInFile("..\\..\\..\\data\\echipe.txt");
            _elevi = new ElevInFile("..\\..\\..\\data\\elevi.txt");
            _meciuri = new MeciInFile("..\\..\\..\\data\\meciuri.txt");
            _jucatori = new JucatorActivInFile("..\\..\\..\\data\\jucatori.txt");
        }

        private Echipa? getEchipaByName(string numeEchipa)
        {
            return _echipe.findAll().Where(echipa => echipa._nume.Equals(numeEchipa)).FirstOrDefault();
        }

        private Echipa? getEchipaByIdJucator(int idJucator)
        {
            return _echipe.findOne(((Jucator)_elevi.findAll().Where(elev => elev._id == idJucator).First())._echipa);
        }

        delegate bool ElevPredicate(Elev elevJucator);
        public static bool ElevJucator(Elev elevJucator)
        {
            return elevJucator.GetType() == typeof(Jucator);
        }

        public void getJucatoriByEchipa(string? numeEchipa)
        {
            if (numeEchipa == null)
            {
                throw new ArgumentNullException("null");
            }

            Echipa? echipa = getEchipaByName(numeEchipa);
            if (echipa == null)
            {
                throw new ArgumentException("Nu exista o echipa cu numele " + numeEchipa);
            }

            ElevPredicate isElevJucator = new ElevPredicate(ElevJucator);

            _elevi.findAll().Where(elev => isElevJucator(elev) && ((Jucator)elev)._echipa == echipa._id).ToList().ForEach(Console.WriteLine);
        }

        private Meci getMeciByEchipeAndData(string numeEchipa1, string numeEchipa2, DateTime dataMeci)
        {
            Echipa? echipa1 = getEchipaByName(numeEchipa1);
            if (echipa1 == null)
            {
                throw new ArgumentException("Nu exista o echipa cu numele " + numeEchipa1);
            }

            Echipa? echipa2 = getEchipaByName(numeEchipa2);
            if (echipa2 == null)
            {
                throw new ArgumentException("Nu exista o echipa cu numele " + numeEchipa2);
            }

            Meci meciCautat = new Meci(0, echipa1._id, echipa2._id, dataMeci);
            return _meciuri.findAll().Where(meci => meciCautat.Equals(meci)).First();
        }

        public void getJucatoriActiviByMeci(string? numeEchipa1, string? numeEchipa2, DateTime dataMeci)
        {
            if (numeEchipa1 == null || numeEchipa2 == null)
            {
                throw new ArgumentNullException("null");
            }

            Meci meci = getMeciByEchipeAndData(numeEchipa1, numeEchipa2, dataMeci);
            if (meci == null)
            {
                throw new ArgumentException("Nu exista un meci intre cele 2 echipe: " + numeEchipa1 + " si " + numeEchipa2);
            }

            _jucatori.findAll().Where(jucator => jucator._idMeci == meci._id).ToList().ForEach(jucator =>
            {
                Console.WriteLine(_elevi.findOne(jucator._idJucator) + " | " + jucator._tipJucator);
            });
        }

        public void getMeciuriByPerioada(DateTime dataStart, DateTime dataEnd)
        {
            _meciuri.findAll().Where(meci => meci._data >= dataStart && meci._data <= dataEnd).ToList().ForEach(meci =>
            {
                Echipa? echipaGazda = _echipe.findOne(meci._echipaGazda);
                Echipa? echipaDeplasare = _echipe.findOne(meci._echipaDeplasare);
                if (echipaGazda == null || echipaDeplasare == null)
                {
                    return;
                }

                Console.WriteLine(echipaGazda._nume + " | " + echipaDeplasare._nume + " | " + meci._data);
            });
        }

        delegate bool JucatorPredicate(JucatorActiv jucator);
        public static bool JucatorParticipant(JucatorActiv jucator)
        {
            return jucator._tipJucator == TipJucator.Participant;
        }

        public void getScoreByMeci(string? numeEchipa1, string? numeEchipa2, DateTime dataMeci)
        {
            if (numeEchipa1 == null || numeEchipa2 == null)
            {
                throw new ArgumentNullException("null");
            }

            Meci meci = getMeciByEchipeAndData(numeEchipa1, numeEchipa2, dataMeci);
            if (meci == null)
            {
                throw new ArgumentException("Nu exista un meci intre cele 2 echipe: " + numeEchipa1 + " si " + numeEchipa2);
            }

            JucatorPredicate isParticipant = new JucatorPredicate(JucatorParticipant);

            int puncteEchipaGazda = 0;
            int puncteEchipaDeplasare = 0;
            _jucatori.findAll().Where(jucator => jucator._idMeci == meci._id && isParticipant(jucator)).ToList().ForEach(jucator =>
            {
                Echipa? echipaJucator = getEchipaByIdJucator(jucator._idJucator);
                if (echipaJucator == null)
                {
                    return;
                }

                if (echipaJucator._id == meci._echipaGazda)
                {
                    puncteEchipaGazda += jucator._nrPuncte;
                }
                else
                {
                    puncteEchipaDeplasare += jucator._nrPuncte;
                }
            });

            Echipa? echipa1 = _echipe.findOne(meci._echipaGazda);
            Echipa? echipa2 = _echipe.findOne(meci._echipaDeplasare);
            if (echipa1 == null || echipa2 == null)
            {
                return;
            }

            Console.WriteLine(echipa1._nume + " " + puncteEchipaGazda + " - " + puncteEchipaDeplasare + " " + echipa2._nume);
        }
    }
}