using lab_8.domain;

namespace lab_8.repository.file
{
    internal class ElevInFile : AbstractInFile<int, Elev>
    {
        public ElevInFile(string filename) : base(filename) { }
        protected override Elev getEntity(List<string> attributes)
        {
            if (attributes.Count == 4)
            {
                return new Jucator(int.Parse(attributes[0]), attributes[1], attributes[2], int.Parse(attributes[3]));
            }

            return new Elev(int.Parse(attributes[0]), attributes[1], attributes[2]);
        }

        protected override string entityAsString(Elev entity)
        {
            return entity.ToString();
        }
    }
}