#pragma once

#include <ostream>
#include <vector>
#include "Film.hpp"

class Valid
{
	public:
		void validate(const Film& film);
};

class ValidateException : public std::exception
{
	std::vector<std::string> msg;

	public:
		ValidateException(const std::vector<std::string>& msg) : std::exception(), msg{ msg } { }

		friend std::ostream& operator<<(std::ostream& out, const ValidateException& ex);
};
