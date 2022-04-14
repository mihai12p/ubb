#include <random>
#include <iostream>
#include <algorithm>
#include "Consola.hpp"

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

	srv.modificaFilm(titlu, titluNou, genNou, anNou, actorNou);
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

	srv.cautaFilm(titlu);
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

void Consola::inchiriazaUi()
{
	FILE* input = __acrt_iob_func(0);
	if (input)
		fseek(input, 0, SEEK_SET);
	std::string titlu;
	std::cout << "Titlu: ";
	std::getline(std::cin, titlu);

	srv.inchiriazaFilm(titlu);
	std::cout << "Filmul a fost inchiriat cu succes.\n";
}

void Consola::golesteUi()
{
	srv.golesteCos();
	std::cout << "Cosul a fost golit cu succes.\n";
}

void Consola::genereazaUi()
{
	int nr;
	std::cout << "Introduceti numarul de generari in cos: ";
	std::cin >> nr;

	std::mt19937 mt{ std::random_device{}() };
	const std::uniform_int_distribution<> dist(0, srv.getAll().size() - 1);
	
	while (nr--)
	{
		const int rndNr = dist(mt);
		srv.inchiriazaFilm(srv.getAll().at(rndNr).getTitlu());
	}
	std::cout << "Cosul a fost generat cu succes.\n";
}

void Consola::raportUi()
{
	std::cout << "\n************************************************************************\nRaport an/inchirieri: \n";
	const std::unordered_map<int, int>& map = srv.raport();
	std::for_each(map.begin(), map.end(), [](const std::pair<int, int>& elem)
	{
		std::cout << "\tAn: " << elem.first << " | Numar inchirieri: " << elem.second << '\n';
	});
	std::cout << "************************************************************************\n";
}

void Consola::tipareste(const std::vector<Film>& filme)
{
	std::cout << "\n************************************************************************\nFilme: \n";
	int index = 0;

	std::for_each(filme.begin(), filme.end(), [&index](const Film& film) 
	{ 
			std::cout << '\t' << ++index << ". " << film.getTitlu() << " | " << film.getGen() << " | " << film.getAn() << " | " << film.getActor(); 
			if (film.getInchiriat() > 0) 
				std::cout << " | INCHIRIAT x " << film.getInchiriat(); 
			std::cout << '\n'; 
	});
	std::cout << "\n\tMomentan sunt " << srv.getCos() << " filme inchiriate in cos.\n";
	std::cout << "************************************************************************\n";
}

void Consola::start()
{
	bool gata = false;
	while (gata == false)
	{
		std::cout << "Meniu: \n\t1 - adauga\n\t2 - sterge\n\t3 - modifica\n\t4 - cauta\n\t5 - filtreaza\n\t6 - sorteaza\n\t7 - adauga in cos\n\t8 - goleste cos\n\t9 - genereaza\n\t10 - raport\n\t11 - tipareste\n\t12 - iesire\n>>>";
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
				inchiriazaUi();
			else if (opt == 8)
				golesteUi();
			else if (opt == 9)
				genereazaUi();
			else if (opt == 10)
				raportUi();
			else if (opt == 11)
			{
				if (&srv)
					tipareste(srv.getAll());
			}
			else if (opt == 12)
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

		if ((opt >= 1 && opt <= 4) || (opt >= 7 && opt <= 10))
			if (&srv)
				tipareste(srv.getAll());
		std::cout << '\n';
	}
}
