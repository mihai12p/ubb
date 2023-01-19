using lab_8.domain;

namespace lab_8.repository.file
{
    internal class JucatorActivInFile : AbstractInFile<int, JucatorActiv>
    {
        public JucatorActivInFile(string filename) : base(filename) { }
        protected override JucatorActiv getEntity(List<string> attributes)
        {
            return new JucatorActiv(int.Parse(attributes[0]), int.Parse(attributes[1]), int.Parse(attributes[2]), int.Parse(attributes[3]), (TipJucator)Enum.Parse(typeof(TipJucator), attributes[4]));
        }

        protected override string entityAsString(JucatorActiv entity)
        {
            return entity.ToString();
        }
    }
}