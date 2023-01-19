using lab_8.domain;

namespace lab_8.repository.file
{
    internal abstract class AbstractInFile<ID, E> : Repository<ID, E> where E : Entitate<ID> where ID : notnull
    {
        private string _numeFisier { get; set; }
        private readonly Dictionary<ID, E> _entitati;

        protected AbstractInFile(string numeFisier)
        {
            _numeFisier = numeFisier;
            _entitati = new Dictionary<ID, E>();

            incarcaDate();
        }

        private void incarcaDate()
        {
            string[] lines = System.IO.File.ReadAllLines(_numeFisier);
            foreach (string line in lines)
            {
                E entity = getEntity(line.Split(';').ToList());
                save(entity);
            }
        }

        protected abstract E getEntity(List<string> attributes);
        protected abstract string entityAsString(E entity);

        public E? findOne(ID id)
        {
            return _entitati.GetValueOrDefault(id);
        }

        public IEnumerable<E> findAll()
        {
            return _entitati.Values;
        }

        public E? save(E e)
        {
            if (e == null)
            {
                throw new ArgumentNullException("entity must not be null");
            }

            if (e._id == null)
            {
                throw new ArgumentNullException("entity must have a valid id");
            }

            foreach (E entity in _entitati.Values)
            {
                if (entity.Equals(e))
                {
                    return entity;
                }
            }

            if (_entitati.ContainsKey(e._id))
            {
                return e;
            }

            _entitati.Add(e._id, e);
            return null;
        }

        public E? remove(ID id)
        {
            _entitati.Remove(id);
            return null;
        }

        public E? update(E e)
        {
            if (e == null)
            {
                throw new ArgumentNullException("entity must not be null");
            }

            if (e._id == null)
            {
                throw new ArgumentNullException("entity must have a valid id");
            }

            if (_entitati.ContainsKey(e._id))
            {
                _entitati.Add(e._id, e);
                return null;
            }

            return e;
        }
    }
}