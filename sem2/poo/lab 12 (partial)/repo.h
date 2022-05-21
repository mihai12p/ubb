#pragma once

#include "joc.h"
#include <vector>

class repo
{
	std::vector<joc> all;

	public:
		const std::vector<joc>& getAll() { return this->all; }

		void adauga(const joc& nou) { all.push_back(nou); }
};

