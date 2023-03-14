using mpp_proiect_csharp_vreauladudu.domain;

namespace mpp_proiect_csharp_vreauladudu.repository.database
{
    internal abstract class AbstractDatabase<ID, E> : IRepository<ID, E> where E : Entity<ID>
    {
        public String? host { get; set; }
        public String? username { get; set; }
        public String? password { get; set; }
        public String? table { get; set; }

        protected AbstractDatabase(string? host, string? username, string? password, string? table)
        {
            this.host = host;
            this.username = username;
            this.password = password;
            this.table = table;
        }

        public E? find(ID id)
        {
            if (id == null)
            {
                throw new ArgumentNullException("entity must not be null");
            }

            return null;
        }

        public IEnumerable<E> findAll()
        {
            return null;
        }

        public E? save(E e)
        {
            return null;
        }

        public E? remove(ID id)
        {
            if (id == null)
            {
                throw new ArgumentNullException("entity must not be null");
            }

            return null;
        }
        public E? update(E e)
        {
            return null;
        }
    }
}