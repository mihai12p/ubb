namespace lab_8.domain
{
    internal class Echipa : Entitate<int>
    {
        public string _nume { get; set; }

        public Echipa(int id, string nume)
        {
            _id = id;
            _nume = nume;
        }

        public override string ToString()
        {
            return _id.ToString() + " | " + _nume;
        }
    }
}