#include <iostream>
#include <algorithm>
#include "Consola.hpp"

void Consola::adaugaCateva()
{
	srv.adaugaFilm("Tom si Jerry", "Amuzzament", 1940, "Jerry");
	srv.adaugaFilm("Miami Bici", "Amuzzament", 2020, "Codin Maticiuc");
	srv.adaugaFilm("Moartea", "Documentar", 2022, "Ion Iliescu");
	srv.adaugaFilm("Soacra mea e o scorpie", "Romance", 2005, "Jane Fonda");
}

void Consola::adaugaUi()
{
	FILE* input = __acrt_iob_func(0);
	if (input)
		fseek(input, 0, SEEK_SET);
	std::string titlu;
	std::cout << "Titlu: ";
	std::getline(std::cin, titlu);
	
	if (input)
		fseek(input, 0, SEEK_SET);
	std::string gen;
	std::cout << "Gen: ";
	std::getline(std::cin, gen);

	int an;
	std::cout << "An: ";
	std::cin >> an;

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string actor;
	std::cout << "Actor: ";
	std::getline(std::cin, actor);

	srv.adaugaFilm(titlu, gen, an, actor);
	std::cout << "Filmul a fost adaugat cu succes.\n";
}

void Consola::stergeUi()
{
	FILE* input = __acrt_iob_func(0);
	if (input)
		fseek(input, 0, SEEK_SET);
	std::string titlu;
	std::cout << "Titlu: ";
	std::getline(std::cin, titlu);

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string gen;
	std::cout << "Gen: ";
	std::getline(std::cin, gen);

	int an;
	std::cout << "An: ";
	std::cin >> an;

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string actor;
	std::cout << "Actor: ";
	std::getline(std::cin, actor);

	srv.stergeFilm(titlu, gen, an, actor);
	std::cout << "Filmul a fost sters cu succes.\n";
}

void Consola::modificaUi()
{
	FILE* input = __acrt_iob_func(0);
	if (input)
		fseek(input, 0, SEEK_SET);
	std::string titlu;
	std::cout << "Titlu: ";
	std::getline(std::cin, titlu);

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string gen;
	std::cout << "Gen: ";
	std::getline(std::cin, gen);

	int an;
	std::cout << "An: ";
	std::cin >> an;

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string actor;
	std::cout << "Actor: ";
	std::getline(std::cin, actor);


	if (input)
		fseek(input, 0, SEEK_SET);
	std::string titluNou;
	std::cout << "Titlu nou: ";
	std::getline(std::cin, titluNou);

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string genNou;
	std::cout << "Gen nou: ";
	std::getline(std::cin, genNou);

	int anNou;
	std::cout << "An nou: ";
	std::cin >> anNou;

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string actorNou;
	std::cout << "Actor nou: ";
	std::getline(std::cin, actorNou);

	srv.modificaFilm(titlu, gen, an, actor, titluNou, genNou, anNou, actorNou);
	std::cout << "Filmul a fost modificat cu succes.\n";
}

void Consola::cautaUi()
{
	FILE* input = __acrt_iob_func(0);
	if (input)
		fseek(input, 0, SEEK_SET);
	std::string titlu;
	std::cout << "Titlu: ";
	std::getline(std::cin, titlu);

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string gen;
	std::cout << "Gen: ";
	std::getline(std::cin, gen);

	int an;
	std::cout << "An: ";
	std::cin >> an;

	if (input)
		fseek(input, 0, SEEK_SET);
	std::string actor;
	std::cout << "Actor: ";
	std::getline(std::cin, actor);

	srv.cautaFilm(titlu, gen, an, actor);
	std::cout << "Filmul a fost gasit cu succes.\n";
}

void Consola::filtreazaUi()
{
	FILE* input = __acrt_iob_func(0);
	if (input)
		fseek(input, 0, SEEK_SET);
	std::string titlu;
	std::cout << "Titlu: ";
	std::getline(std::cin, titlu);

	int an;
	std::cout << "An: ";
	std::cin >> an;

	tipareste(srv.filtrare(titlu, an));
}

void Consola::sorteazaUi()
{
	int criteriu;
	std::cout << "Criterii: 1 - titlu, 2 - actor, 3 - an + gen\n";
	std::cin >> criteriu;
	
	tipareste(srv.sortare(criteriu));
}

void Consola::tipareste(const std::vector<Film>& filme)
{
	std::cout << "\n*************************************************\nFilme: \n";
	int index = 0;

	std::for_each(filme.begin(), filme.end(), [&index](const Film& film) { std::cout << '\t' << ++index << ". " << film.getTitlu() << " | " << film.getGen() << " | " << film.getAn() << " | " << film.getActor() << '\n'; });
	std::cout << "*************************************************\n";
}

void Consola::start()
{
	bool gata = false;
	while (gata == false)
	{
		std::cout << "Meniu: \n\t1 - adauga\n\t2 - sterge\n\t3 - modifica\n\t4 - cauta\n\t5 - filtreaza\n\t6 - sorteaza\n\t7 - tipareste\n\t8 - iesire\n>>>";
		int opt;
		std::cin >> opt;
		try
		{
			if (opt == 1)
				adaugaUi();
			else if (opt == 2)
				stergeUi();
			else if (opt == 3)
				modificaUi();
			else if (opt == 4)
				cautaUi();
			else if (opt == 5)
				filtreazaUi();
			else if (opt == 6)
				sorteazaUi();
			else if (opt == 7)
			{
				if (&srv)
					tipareste(srv.getAll());
			}
			else if (opt == 8)
				gata = true;
			else
				std::cout << "Comanda invalida.\n";
		}
		catch (const ValidateException& ex)
		{
			std::cout << "EXCEPTIE VALIDARE: " << ex << '\n';
		}
		catch (const FilmeException& ex)
		{
			std::cout << "EXCEPTIE VALIDARE: " << ex << '\n';
		}

		if (opt >= 1 && opt <= 4)
			if (&srv)
				tipareste(srv.getAll());
		std::cout << '\n';
	}
}
