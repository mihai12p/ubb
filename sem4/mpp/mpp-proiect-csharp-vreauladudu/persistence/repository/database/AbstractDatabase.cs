using mpp_proiect_csharp_vreauladudu.domain;
using System;
using System.Data.SQLite;
using System.Collections.Generic;

namespace mpp_proiect_csharp_vreauladudu.repository.database
{
    public abstract class AbstractDatabase<ID, E> : IRepository<ID, E> where E : Entity<ID>
    {
        public String Table { get; set; }
        private static readonly log4net.ILog logger = log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

        protected AbstractDatabase(string table)
        {
            this.Table = table;
        }

        protected abstract E extractEntity(SQLiteDataReader result);

        protected abstract SQLiteCommand findStatement(ID id);
        protected abstract SQLiteCommand saveStatement(E entity);
        protected abstract SQLiteCommand deleteStatement(ID id);
        protected abstract SQLiteCommand updateStatement(E entity);

        public E find(ID id)
        {
            logger.Info("Entry");
            if (id == null)
            {
                throw new ArgumentNullException("entity must not be null");
            }

            try
            {
                using (SQLiteDataReader result = findStatement(id).ExecuteReader())
                {
                    while (result.Read())
                    {
                        E entity = this.extractEntity(result);
                        logger.Info(entity);
                        return entity;
                    }
                }
            }
            catch (SQLiteException exception)
            {
                logger.Error(exception.Message);
                Console.Write(exception.StackTrace);
            }

            logger.Info("Exit");
            return null;
        }

        public IEnumerable<E> findAll()
        {
            logger.Info("Entry");
            HashSet<E> entities = new HashSet<E>();
            try
            {
                SQLiteConnection connection = DatabaseUtils.GetConnection();
                using (SQLiteCommand command = connection.CreateCommand())
                {
                    command.CommandText = "SELECT * FROM " + this.Table;
                    using (SQLiteDataReader result = command.ExecuteReader())
                    {
                        while (result.Read())
                        {
                            entities.Add(this.extractEntity(result));
                        }
                    }
                }
            }
            catch (SQLiteException exception)
            {
                logger.Error(exception.Message);
                Console.Write(exception.StackTrace);
            }

            logger.Info(entities);
            return entities;
        }

        public E save(E e)
        {
            logger.Info("Entry");
            E searchedEntity = this.find(e.Id);
            if (searchedEntity != null)
            {
                logger.Info(searchedEntity);
                return searchedEntity;
            }

            try
            {
                SQLiteConnection connection = DatabaseUtils.GetConnection();
                this.saveStatement(e).ExecuteNonQuery();
            }
            catch (SQLiteException exception)
            {
                logger.Error(exception.Message);
                Console.Write(exception.StackTrace);
            }

            E savedEntity = this.find(e.Id);
            logger.Info(savedEntity);
            return savedEntity;
        }

        public E remove(ID id)
        {
            logger.Info("Entry");
            if (id == null)
            {
                throw new ArgumentNullException("entity must not be null");
            }

            E searchedEntity = this.find(id);
            if (searchedEntity != null)
            {
                try
                {
                    SQLiteConnection connection = DatabaseUtils.GetConnection();
                    this.deleteStatement(id).ExecuteNonQuery();
                }
                catch (SQLiteException exception)
                {
                    logger.Error(exception.Message);
                    Console.Write(exception.StackTrace);
                }
            }

            logger.Info(searchedEntity);
            return searchedEntity;
        }
        public E update(E entity)
        {
            logger.Info("Entry");
            try
            {
                SQLiteConnection connection = DatabaseUtils.GetConnection();
                this.updateStatement(entity).ExecuteNonQuery();
            }
            catch (SQLiteException exception)
            {
                logger.Error(exception.Message);
                Console.Write(exception.StackTrace);
            }

            logger.Info(entity);
            return entity;
        }
    }
}