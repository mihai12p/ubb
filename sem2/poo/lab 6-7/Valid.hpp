#pragma once

#include "MyDynaVec.hpp"
#include <ostream>
#include "Film.hpp"

class Valid
{
	public:
		void validate(const Film& film);
};

class ValidateException
{
	MyDynaVec<std::string> msg;

	public:
		ValidateException(const MyDynaVec<std::string>& msg) : msg{ msg } { }

		friend std::ostream& operator<<(std::ostream& out, const ValidateException& ex);
};
