using lab_8.domain;

namespace lab_8.repository.file
{
    internal class EchipaInFile : AbstractInFile<int, Echipa>
    {
        public EchipaInFile(string filename) : base(filename) {}

        protected override Echipa getEntity(List<string> attributes)
        {
            return new Echipa(int.Parse(attributes[0]), attributes[1]);
        }

        protected override string entityAsString(Echipa entity)
        {
            return entity.ToString();
        }
    }
}