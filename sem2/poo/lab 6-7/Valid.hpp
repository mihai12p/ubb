#pragma once

#include <vector>
#include <ostream>
#include "Film.hpp"

class Valid
{
	public:
		void validate(const Film& film);
};

class ValidateException
{
	std::vector<std::string> msg;

	public:
		ValidateException(const std::vector<std::string>& msg) : msg{ msg } { }

		friend std::ostream& operator<<(std::ostream& out, const ValidateException& ex);
};
