namespace lab_8.domain
{
    internal class Jucator : Elev
    {
        public int _echipa { get; set; }

        public Jucator(int id, string nume, string scoala, int echipa) : base(id, nume, scoala)
        {
            _echipa = echipa;
        }
    }
}