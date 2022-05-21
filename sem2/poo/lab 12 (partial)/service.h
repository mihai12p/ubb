#pragma once

#include "repo.h"

class service
{
	repo& r;

	public:
		service(repo& r) : r{ r }
		{
			loadFromFile("jocuri.txt");
		}

		const std::vector<joc>& getAll() { return r.getAll(); }

		void adauga(const int idx, const std::string& titlu, const int pret, const std::string& platf, const int pegi);
		std::vector<joc> sortare();
		std::vector<joc> filtrare();

		void loadFromFile(const std::string& fileName);
};

