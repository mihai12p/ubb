namespace lab_8.domain
{
    internal class Elev : Entitate<int>
    {
        private string _nume { get; set; }
        private string _scoala { get; set; }

        public Elev(int id, string nume, string scoala)
        {
            _id = id;
            _nume = nume;
            _scoala = scoala;
        }

        public override string ToString()
        {
            return _id.ToString() + " | " + _nume + " | " + _scoala;
        }
    }
}