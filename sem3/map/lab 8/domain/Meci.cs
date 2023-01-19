namespace lab_8.domain
{
    internal class Meci : Entitate<int>
    {
        public int _echipaGazda { get; set; }
        public int _echipaDeplasare { get; set; }
        public DateTime _data { get; set; }

        public Meci(int id, int echipaGazda, int echipaDeplasare, DateTime data)
        {
            _id = id;
            _echipaGazda = echipaGazda;
            _echipaDeplasare = echipaDeplasare;
            _data = data;
        }

        public override string ToString()
        {
            return _id.ToString() + ' ' + _echipaGazda + ' ' + _echipaDeplasare + ' ' + _data;
        }

        public override bool Equals(object? obj)
        {
            return obj is Meci meci &&
                   ((_echipaGazda == meci._echipaGazda && _echipaDeplasare == meci._echipaDeplasare) || 
                   (_echipaGazda == meci._echipaDeplasare && _echipaDeplasare == meci._echipaGazda)) &&
                   _data == meci._data;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(_echipaGazda, _echipaDeplasare, _data);
        }
    }
}