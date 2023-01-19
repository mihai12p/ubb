namespace lab_8.domain
{
    internal enum TipJucator : ushort
    {
        Rezerva = 0,
        Participant = 1
    }

    internal class JucatorActiv : Entitate<int>
    {
        public int _idJucator { get; set; }
        public int _idMeci { get; set; }
        public int _nrPuncte { get; set; }
        public TipJucator _tipJucator { get; set; }

        public JucatorActiv(int id, int idJucator, int idMeci, int nrPuncte, TipJucator tipJucator)
        {
            _id = id;
            _idJucator = idJucator;
            _idMeci = idMeci;
            _nrPuncte = nrPuncte;
            _tipJucator = tipJucator;
        }

        public override string ToString()
        {
            return _id.ToString() + ' ' + _idJucator + ' ' + _idMeci + ' ' + _nrPuncte + ' ' + _tipJucator.ToString();
        }
    }
}