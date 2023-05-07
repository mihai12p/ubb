package moto.repository.hibernate;

import moto.User;
import moto.repository.UserRepository;
import org.hibernate.Session;

public class UserHibernate implements UserRepository
{
    @Override
    public User find(Integer id) throws IllegalArgumentException
    {
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        return null;
    }

    @Override
    public Iterable<User> findAll()
    {
        try (Session session = HibernateUtils.getSessionFactory().openSession())
        {
            return session.createQuery("from User", User.class).list();
        }
    }

    @Override
    public User save(User user)
    {
        return null;
    }

    @Override
    public User remove(Integer id) throws IllegalArgumentException
    {
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }

        return null;
    }

    @Override
    public User update(User user)
    {
        return null;
    }

    @Override
    public User isValidUser(String username, String password)
    {
        try (Session session = HibernateUtils.getSessionFactory().openSession())
        {
            return session.createQuery("from User where username = :username and password = :password", User.class)
                    .setParameter("username", username)
                    .setParameter("password", password)
                    .uniqueResult();
        }
    }
}
