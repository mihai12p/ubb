using lab_8.domain;

namespace lab_8.repository.file
{
    internal class MeciInFile : AbstractInFile<int, Meci>
    {
        public MeciInFile(string filename) : base(filename) { }
        protected override Meci getEntity(List<string> attributes)
        {
            return new Meci(int.Parse(attributes[0]), int.Parse(attributes[1]), int.Parse(attributes[2]), DateTime.Parse(attributes[3]));
        }

        protected override string entityAsString(Meci entity)
        {
            return entity.ToString();
        }
    }
}