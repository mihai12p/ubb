#pragma once

#include "Service.hpp"

class Consola
{
	Service& srv;

	void adaugaUi();
	void stergeUi();
	void modificaUi();
	void cautaUi();
	void filtreazaUi();
	void sorteazaUi();
	void inchiriazaUi();
	void golesteUi();
	void genereazaUi();
	void raportUi();
	void tipareste(const std::vector<Film>& filme);

	public:
		Consola(Service& srv) noexcept : srv{ srv } { }
		Consola(const Consola& other) = delete;

		void start();
};
