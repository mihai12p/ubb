package moto.repository;

import moto.User;

import java.sql.SQLException;

public interface UserRepository extends IRepository<Integer, User>
{
    User isValidUser(String username, String password) throws SQLException;
}