#pragma once

#include "Service.hpp"

class Consola
{
	Service& srv;

	void adaugaUi();
	void stergeUi();
	void modificaUi();
	void cautaUi();
	void tipareste(const std::vector<Film>& filme);

	public:
		Consola(Service& srv) noexcept : srv{ srv } { }
		Consola(const Consola& other) = delete;

		void adaugaCateva();
		void start();
};
