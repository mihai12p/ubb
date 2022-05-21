#pragma once

#include <string>

class joc
{
	int idx;
	std::string titlu;
	int pret;
	std::string platf;
	int pegi;

	public:
		joc(const int idx, const std::string& titlu, const int pret, const std::string& platf, const int pegi) : idx{ idx }, titlu { titlu }, pret{ pret }, platf{ platf }, pegi{ pegi } { }

		const int getIdx() const noexcept { return this->idx; }
		const std::string& getTitlu() const noexcept { return this->titlu; }
		const int getPret() const noexcept { return this->pret; }
		const std::string& getPlatf() const noexcept { return this->platf; }
		const int getPegi() const noexcept { return this->pegi; }
};

