#pragma once

#include <unordered_map>
#include "Repo.hpp"
#include "Valid.hpp"

class ActiuneUndo
{
	public:
		ActiuneUndo() noexcept { }
		virtual ~ActiuneUndo() { }

		ActiuneUndo(const ActiuneUndo& other) = default; // constructor de copiere
		ActiuneUndo& operator=(const ActiuneUndo& other) = default; // assignment operator
		ActiuneUndo(ActiuneUndo&& other) noexcept = default; // move constructor
		ActiuneUndo& operator=(ActiuneUndo&& other) = default; // move assignment

		virtual void doUndo() = 0;
};

class UndoAdauga : public ActiuneUndo
{
	Filme& repo;
	Film filmAdaugat;

	public:
		UndoAdauga(Filme& repo, const Film& filmAdaugat) : ActiuneUndo(), repo{ repo }, filmAdaugat{ filmAdaugat } { }

		void doUndo() override { repo.sterge(filmAdaugat); }
};

class UndoSterge : public ActiuneUndo
{
	Filme& repo;
	Film filmSters;

	public:
		UndoSterge(Filme& repo, const Film& filmSters) : ActiuneUndo(), repo{ repo }, filmSters{ filmSters } { }

		void doUndo() override { repo.adauga(filmSters); }
};

class UndoModifica : public ActiuneUndo
{
	Filme& repo;
	Film filmDeModificat;
	Film filmDupaModificare;

	public:
		UndoModifica(Filme& repo, const Film& filmDeModificat, Film& filmDupaModificare) : ActiuneUndo(), repo{ repo }, filmDeModificat{ filmDeModificat }, filmDupaModificare{ filmDupaModificare } { }

		void doUndo() override { repo.modifica(filmDeModificat, filmDupaModificare); }
};

class Service
{
	Filme& repo;
	Valid& valid;

	std::list<std::unique_ptr<ActiuneUndo>> undo;

	typedef const bool(*functie)(const Film& f1, const Film& f2);

	public:
		Service(Filme& repo, Valid& valid) noexcept : repo{ repo }, valid{ valid } { }
		Service(const Service& other) = delete;

		const std::vector<Film>& getAll() const noexcept { return repo.getAll(); }
		const int getCos() const noexcept { return repo.getCos(); }

		void adaugaFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor);
		void stergeFilm(const std::string& titlu, const std::string& gen, const int an, const std::string& actor);
		const size_t modificaFilm(const std::string& titlu, const std::string& titluNou, const std::string& genNou, const int anNou, const std::string& actorNou);
		const std::unique_ptr<Film> cautaFilm(const std::string& titlu) const;
		const std::vector<Film> filtrare(const std::string& titlu, const int an);
		const std::vector<Film> sortare(int criteriu);
		void inchiriazaFilm(const std::string& titlu);
		void golesteCos() noexcept { repo.golesteCos(); }
		const std::unordered_map<int, int> raport() const noexcept;

		void saveToFile(const std::string& fileName);
		void undoLast();
};
